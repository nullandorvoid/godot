import os
import sys
import string
import platform


def is_active():
    return True


def get_name():
    return "Android"


def can_build():

    import os
    if (not ("ANDROID_NDK_ROOT" in os.environ)):
        return False

    return True


def get_opts():

    return [
        ('ANDROID_NDK_ROOT', 'the path to Android NDK',
         os.environ.get("ANDROID_NDK_ROOT", 0)),
	('ndk_platform', 'compile for platform: (android-<api> , example: android-18)', "android-18"),
        ('android_arch', 'select compiler architecture: (armv7/armv6/x86)', "armv7"),
        ('android_neon', 'enable neon (armv7 only)', "yes"),
        ('android_stl', 'enable STL support in android port (for modules)', "no")
    ]


def get_flags():

    return [
        ('tools', 'no'),
    ]


def create(env):
    tools = env['TOOLS']
    if "mingw" in tools:
        tools.remove('mingw')
    if "applelink" in tools:
        tools.remove("applelink")
        env.Tool('gcc')
    return env.Clone(tools=tools)


def configure(env):

    # Workaround for MinGW. See:
    # http://www.scons.org/wiki/LongCmdLinesOnWin32
    import os
    if (os.name == "nt"):

        import subprocess

        def mySubProcess(cmdline, env):
            # print "SPAWNED : " + cmdline
            startupinfo = subprocess.STARTUPINFO()
            startupinfo.dwFlags |= subprocess.STARTF_USESHOWWINDOW
            proc = subprocess.Popen(cmdline, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
                                    stderr=subprocess.PIPE, startupinfo=startupinfo, shell=False, env=env)
            data, err = proc.communicate()
            rv = proc.wait()
            if rv:
                print ("=====")
                print (err)
                print ("=====")
            return rv

        def mySpawn(sh, escape, cmd, args, env):

            newargs = ' '.join(args[1:])
            cmdline = cmd + " " + newargs

            rv = 0
            if len(cmdline) > 32000 and cmd.endswith("ar"):
                cmdline = cmd + " " + args[1] + " " + args[2] + " "
                for i in range(3, len(args)):
                    rv = mySubProcess(cmdline + args[i], env)
                    if rv:
                        break
            else:
                rv = mySubProcess(cmdline, env)

            return rv

        env['SPAWN'] = mySpawn

    ndk_platform = env['ndk_platform']

    if env['android_arch'] not in ['armv7', 'armv6', 'x86']:
        env['android_arch'] = 'armv7'

    if env['android_arch'] == 'x86':
        env["x86_libtheora_opt_gcc"] = True

    if env['PLATFORM'] == 'win32':
        env.Tool('gcc')
        env['SHLIBSUFFIX'] = '.so'

    neon_text = ""
    if env["android_arch"] == "armv7" and env['android_neon'] == 'yes':
        neon_text = " (with neon)"
    print("Godot Android!!!!! (" + env['android_arch'] + ")" + neon_text)

    env.Append(CPPPATH=['#platform/android'])

    if env['android_arch'] == 'x86':
        env.extra_suffix = ".x86" + env.extra_suffix
        target_subpath = "x86-4.9"
        abi_subpath = "i686-linux-android"
        arch_subpath = "x86"
    elif env['android_arch'] == 'armv6':
        env.extra_suffix = ".armv6" + env.extra_suffix
        target_subpath = "arm-linux-androideabi-4.9"
        abi_subpath = "arm-linux-androideabi"
        arch_subpath = "armeabi"
    elif env["android_arch"] == "armv7":
        target_subpath = "arm-linux-androideabi-4.9"
        abi_subpath = "arm-linux-androideabi"
        arch_subpath = "armeabi-v7a"
        if env['android_neon'] == 'yes':
            env.extra_suffix = ".armv7.neon" + env.extra_suffix
        else:
            env.extra_suffix = ".armv7" + env.extra_suffix

    mt_link = True
    if (sys.platform.startswith("linux")):
        host_subpath = "linux-x86_64"
    elif (sys.platform.startswith("darwin")):
        host_subpath = "darwin-x86_64"
    elif (sys.platform.startswith('win')):
        if (platform.machine().endswith('64')):
            host_subpath = "windows-x86_64"
        else:
            mt_link = False
            host_subpath = "windows"

    compiler_path = env["ANDROID_NDK_ROOT"] + \
        "/toolchains/llvm/prebuilt/" + host_subpath + "/bin"
    gcc_toolchain_path = env["ANDROID_NDK_ROOT"] + \
        "/toolchains/" + target_subpath + "/prebuilt/" + host_subpath
    tools_path = gcc_toolchain_path + "/" + abi_subpath + "/bin"

    # For Clang to find NDK tools in preference of those system-wide
    env.PrependENVPath('PATH', tools_path)

    env['CC'] = compiler_path + '/clang'
    env['CXX'] = compiler_path + '/clang++'
    env['AR'] = tools_path + "/ar"
    env['RANLIB'] = tools_path + "/ranlib"
    env['AS'] = tools_path + "/as"

    if env['android_arch'] == 'x86':
        env['ARCH'] = 'arch-x86'
    else:
        env['ARCH'] = 'arch-arm'

    sysroot = env["ANDROID_NDK_ROOT"] + \
        "/platforms/" + ndk_platform + "/" + env['ARCH']
    common_opts = ['-fno-integrated-as', '-gcc-toolchain', gcc_toolchain_path]

    env.Append(CPPFLAGS=["-isystem", sysroot + "/usr/include"])
    env.Append(CPPFLAGS=string.split(
        '-fpic -ffunction-sections -funwind-tables -fstack-protector-strong -fvisibility=hidden -fno-strict-aliasing'))
    env.Append(CPPFLAGS=string.split('-DANDROID -DNO_STATVFS -DGLES2_ENABLED'))

    env['neon_enabled'] = False
    if env['android_arch'] == 'x86':
        can_vectorize = True
        target_opts = ['-target', 'i686-none-linux-android']
        # The NDK adds this if targeting API < 21, so we can drop it when Godot targets it at least
        env.Append(CPPFLAGS=['-mstackrealign'])
    elif env["android_arch"] == "armv6":
        can_vectorize = False
        target_opts = ['-target', 'armv6-none-linux-androideabi']
        env.Append(CPPFLAGS=string.split(
            '-D__ARM_ARCH_6__ -march=armv6 -mfpu=vfp -mfloat-abi=softfp'))
    elif env["android_arch"] == "armv7":
        can_vectorize = True
        target_opts = ['-target', 'armv7-none-linux-androideabi']
        env.Append(CPPFLAGS=string.split(
            '-D__ARM_ARCH_7__ -D__ARM_ARCH_7A__ -march=armv7-a -mfloat-abi=softfp'))
        if env['android_neon'] == 'yes':
            env['neon_enabled'] = True
            env.Append(CPPFLAGS=['-mfpu=neon', '-D__ARM_NEON__'])
        else:
            env.Append(CPPFLAGS=['-mfpu=vfpv3-d16'])

    env.Append(CPPFLAGS=target_opts)
    env.Append(CPPFLAGS=common_opts)

    env.Append(LIBS=['OpenSLES'])
    env.Append(LIBS=['EGL', 'OpenSLES', 'android'])
    env.Append(LIBS=['log', 'GLESv1_CM', 'GLESv2', 'GLESv3','z'])

    if (sys.platform.startswith("darwin")):
        env['SHLIBSUFFIX'] = '.so'

    env['LINKFLAGS'] = ['-shared', '--sysroot=' +
                        sysroot, '-Wl,--warn-shared-textrel']
    env.Append(LINKFLAGS=string.split(
        '-Wl,--fix-cortex-a8'))
    env.Append(LINKFLAGS=string.split(
        '-Wl,--no-undefined -Wl,-z,noexecstack -Wl,-z,relro -Wl,-z,now'))
    env.Append(LINKFLAGS=string.split(
        '-Wl,-soname,libgodot_android.so -Wl,--gc-sections'))
    if mt_link:
        env.Append(LINKFLAGS=['-Wl,--threads'])
    env.Append(LINKFLAGS=target_opts)
    env.Append(LINKFLAGS=common_opts)

    env.Append(LIBPATH=[env["ANDROID_NDK_ROOT"] + '/toolchains/arm-linux-androideabi-4.9/prebuilt/' +
                        host_subpath + '/lib/gcc/' + abi_subpath + '/4.9.x'])
    env.Append(LIBPATH=[env["ANDROID_NDK_ROOT"] +
                        '/toolchains/arm-linux-androideabi-4.9/prebuilt/' + host_subpath + '/' + abi_subpath + '/lib'])

    if (env["target"].startswith("release")):
        env.Append(LINKFLAGS=['-O2'])
        env.Append(CPPFLAGS=['-O2', '-DNDEBUG', '-ffast-math',
                             '-funsafe-math-optimizations', '-fomit-frame-pointer'])
        if (can_vectorize):
            env.Append(CPPFLAGS=['-ftree-vectorize'])
        if (env["target"] == "release_debug"):
            env.Append(CPPFLAGS=['-DDEBUG_ENABLED'])
    elif (env["target"] == "debug"):
        env.Append(LINKFLAGS=['-O0'])
        env.Append(CPPFLAGS=['-O0', '-D_DEBUG', '-UNDEBUG', '-DDEBUG_ENABLED',
                             '-DDEBUG_MEMORY_ALLOC', '-g', '-fno-limit-debug-info'])

    env.Append(CPPFLAGS=['-DANDROID_ENABLED',
                         '-DUNIX_ENABLED', '-DNO_FCNTL', '-DMPC_FIXED_POINT'])

    # TODO: Move that to opus module's config
    if("module_opus_enabled" in env and env["module_opus_enabled"] != "no"):
        if (env["android_arch"] == "armv6" or env["android_arch"] == "armv7"):
            env.Append(CFLAGS=["-DOPUS_ARM_OPT"])
        env.opus_fixed_point = "yes"

    if (env['android_stl'] == 'yes'):
        env.Append(CPPPATH=[env["ANDROID_NDK_ROOT"] +
                            "/sources/cxx-stl/gnu-libstdc++/4.9/include"])
        env.Append(CPPPATH=[env["ANDROID_NDK_ROOT"] +
                            "/sources/cxx-stl/gnu-libstdc++/4.9/libs/" + arch_subpath + "/include"])
        env.Append(LIBPATH=[env["ANDROID_NDK_ROOT"] +
                            "/sources/cxx-stl/gnu-libstdc++/4.9/libs/" + arch_subpath])
        env.Append(LIBS=["gnustl_static"])
    else:
        env.Append(CXXFLAGS=['-fno-rtti', '-fno-exceptions', '-DNO_SAFE_CAST'])

    import methods
    env.Append(BUILDERS={'GLSL120': env.Builder(
        action=methods.build_legacygl_headers, suffix='glsl.h', src_suffix='.glsl')})
    env.Append(BUILDERS={'GLSL': env.Builder(
        action=methods.build_glsl_headers, suffix='glsl.h', src_suffix='.glsl')})
    env.Append(BUILDERS={'GLSL120GLES': env.Builder(
        action=methods.build_gles2_headers, suffix='glsl.h', src_suffix='.glsl')})

    env.use_windows_spawn_fix()
