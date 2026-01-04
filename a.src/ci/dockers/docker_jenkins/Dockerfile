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

# JENKINS_HOME=/home/media/jenkins_home
# docker build --no-cache -t jenkins_img .
# docker run -dt --restart unless-stopped --privileged -v /var/run/docker.sock:/var/run/docker.sock -v ${JENKINS_HOME}:/var/jenkins_home -p 8080:8080 -p 50000:50000 --name jenkins_container jenkins_img

# you can use docker volumes to share data, but it causes a problem when nested docker containers are used.
# docker volume create my_space_volume jenkins_home_volume
# docker run -dt --restart unless-stopped --privileged -v /var/run/docker.sock:/var/run/docker.sock -v jenkins_home_volume:/var/jenkins_home -v my_space_volume:/home/my_space_volume -p 8080:8080 -p 50000:50000 --name jenkins_container jenkins_img
# docker volume inspect my_space_volume // shows on H where in fact this volume is mapped.

