FROM jenkins/jenkins:jdk21

#Switching to root instead Jenkins user is needed due to potential problem with permission
USER root
RUN apt-get update && apt-get install -y lsb-release 
RUN apt-get install rsync && zip
RUN apt-get install zip
RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
  https://download.docker.com/linux/debian/gpg
RUN echo "deb [arch=$(dpkg --print-architecture) \
  signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
  https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list

#avaliable plugin https://jenkins-plugin-hub.herokuapp.com/
#Set base plugins. The other you will install via GUI.
RUN apt-get update && apt-get install -y docker-ce-cli
RUN jenkins-plugin-cli --plugins "ssh-credentials:337.v395d2403ccd4 ssh-slaves:2.973.v0fa_8c0dea_f9f github-api:1.318-461.v7a_c09c9fa_d63 pipeline-stage-view:2.34 junit:1279.v72cf99b_25c43"

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