#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/wukong/catkin_ws/src/Advanced-src/arbotix_ros/arbotix_python"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/wukong/catkin_ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/wukong/catkin_ws/install/lib/python2.7/dist-packages:/home/wukong/catkin_ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/wukong/catkin_ws/build" \
    "/usr/bin/python2" \
    "/home/wukong/catkin_ws/src/Advanced-src/arbotix_ros/arbotix_python/setup.py" \
     \
    build --build-base "/home/wukong/catkin_ws/build/Advanced-src/arbotix_ros/arbotix_python" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/wukong/catkin_ws/install" --install-scripts="/home/wukong/catkin_ws/install/bin"
