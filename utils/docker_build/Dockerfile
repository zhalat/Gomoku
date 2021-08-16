#base on debian
FROM debian:stable-slim

# install common utilities
RUN apt-get update \
  && apt-get install --no-install-recommends -y \
    build-essential \
    ca-certificates \
    clang-format \
    cmake \
    cppcheck \
    git \
    libgmock-dev \
    libgtest-dev \
    openssh-server \
    python3 \
    rsync \
    valgrind \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

# Enable ssh connection
RUN echo 'root:admin' | chpasswd
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/g' /etc/ssh/sshd_config
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/g' /etc/ssh/sshd_config
RUN mkdir -p /run/sshd
EXPOSE 22
CMD ["/usr/sbin/sshd", "-D"]