FROM jenkins/jenkins:jdk21

# Switch to root (required for apt installs)
USER root

# Install base OS packages + Docker CLI
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
    lsb-release \
    rsync \
    zip \
    ca-certificates \
    curl \
    gnupg \
 && rm -rf /var/lib/apt/lists/*

# Add Docker official GPG key
RUN mkdir -p /usr/share/keyrings \
 && curl -fsSL https://download.docker.com/linux/debian/gpg \
    | gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg

# Add Docker repository
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] \
https://download.docker.com/linux/debian $(lsb_release -cs) stable" \
> /etc/apt/sources.list.d/docker.list

# Install Docker CLI only (no daemon!)
RUN apt-get update \
 && apt-get install -y --no-install-recommends docker-ce-cli \
 && rm -rf /var/lib/apt/lists/*

# Install Jenkins plugins (pinned versions = reproducible builds)
RUN jenkins-plugin-cli --plugins \
    ssh-credentials:337.v395d2403ccd4 \
    ssh-slaves:2.973.v0fa_8c0dea_f9f \
    github-api:1.318-461.v7a_c09c9fa_d63 \
    pipeline-stage-view:2.34 \
    junit:1279.v72cf99b_25c43

# Switch back to Jenkins user
USER jenkins

#Build & run
# H - host machine; D1 - first container ; D2 container in D1
# docker build --no-cache -t jenkins_img .
# docker volume create jenkins_home_volume  
# docker volume create my_space_volume
# docker run -dt --restart unless-stopped --privileged -v /var/run/docker.sock:/var/run/docker.sock -v jenkins_home_volume:/var/jenkins_home -v my_space_volume:/home/my_space_volume -p 8080:8080 -p 50000:50000 --name jenkins_container jenkins_img
#
# then if you want create container inside jenkins_container and mount my_space_volume where you can put anything which should be sharable between those two.
# You can see that my_space_volume is mapped to  /home/my_space_volume in D1. Put there content so it will be visibe in D2 when you run it as:
#
# docker run -dt \
#   --privileged \
#   -v my_space_volume:/Gomoku \
#   --name gomoku_container \
#   ginar/android_qt6_img:latest /bin/bash

# docker volume inspect my_space_volume  // shows on H where in fact this volume is mapped.