FROM centos:7.4.1708

RUN yum update -y

RUN yum install -y \
    gperf \
    libuuid-devel \
    libxml2-devel \
    boost-devel \
    zlib-devel \
    bzip2-devel \
    sqlite \
    sqlite-devel \
    openssl-devel \
    freetype* \
    libpng-devel \
    libjpeg-devel\
    gcc \
    cmake \
    git \
    gtk2-devel \
    pkgconfig \
    ffmpeg \
    wget \
    which

# Python 3
RUN yum -y install yum-utils
RUN yum -y groupinstall development
RUN yum -y install 'https://centos7.iuscommunity.org/ius-release.rpm'
RUN yum -y install \
    python36u \
    python36u-pip \
    python36u-devel
#RUN ln -s /usr/bin/pydoc3.6 /usr/bin/pydoc3 && \
#    ln -s /usr/bin/python3.6 /usr/bin/python3

# CMake
RUN mkdir -p /tmp/cmake && \
    pushd /tmp/cmake && \
    wget 'https://cmake.org/files/v3.9/cmake-3.9.1-Linux-x86_64.sh' && \
    bash cmake-3.9.1-Linux-x86_64.sh --prefix=/usr/local --exclude-subdir && \
    popd && \
    rm -rf /tmp/cmake

# GCC
RUN yum install -y \
    centos-release-scl
RUN yum install -y \
    devtoolset-7-gcc*
ENV PATH="/opt/rh/devtoolset-7/root/usr/bin:$PATH"
RUN source scl_source enable devtoolset-7

WORKDIR /
ENV OPENCV_VERSION="3.4.6"
RUN wget https://github.com/opencv/opencv/archive/${OPENCV_VERSION}.zip \
&& unzip ${OPENCV_VERSION}.zip \
&& mkdir /opencv-${OPENCV_VERSION}/cmake_binary \
&& cd /opencv-${OPENCV_VERSION}/cmake_binary \
&& cmake -DBUILD_TIFF=ON \
  -DBUILD_opencv_java=OFF \
  -DWITH_CUDA=OFF \
  -DWITH_OPENGL=ON \
  -DWITH_OPENCL=ON \
  -DWITH_IPP=ON \
  -DWITH_TBB=ON \
  -DWITH_EIGEN=ON \
  -DWITH_V4L=ON \
  -DBUILD_TESTS=OFF \
  -DBUILD_PERF_TESTS=OFF \
  -DCMAKE_BUILD_TYPE=RELEASE \
  .. \
&& make install \
&& rm /${OPENCV_VERSION}.zip \
&& rm -r /opencv-${OPENCV_VERSION}

RUN yum clean all

RUN useradd -m user && yes password | passwd user

# Build directory
RUN mkdir -p /src
WORKDIR /src
