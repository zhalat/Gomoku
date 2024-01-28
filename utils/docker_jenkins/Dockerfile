#FROM jenkins/jenkins:lts-jdk11
FROM jenkins/jenkins:jdk11

#This sections is to get acces for repo and install a few plugins like blueocean
#Switching to root instead Jenkins user is needed due to potential problem with permission
USER root
RUN apt-get update && apt-get install -y lsb-release
RUN curl -fsSLo /usr/share/keyrings/docker-archive-keyring.asc \
  https://download.docker.com/linux/debian/gpg
RUN echo "deb [arch=$(dpkg --print-architecture) \
  signed-by=/usr/share/keyrings/docker-archive-keyring.asc] \
  https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" > /etc/apt/sources.list.d/docker.list

#avaliable plugin https://jenkins-plugin-hub.herokuapp.com/
RUN apt-get update && apt-get install -y docker-ce-cli
RUN jenkins-plugin-cli --plugins "blueocean:1.25.2 docker-workflow:1.26"
RUN jenkins-plugin-cli --plugins pipeline-model-definition github-branch-source:1.8

#Build & run
#'docker build -t jenkins_img .'
#'docker run -d --restart unless-stopped --privileged -v /var/run/docker.sock:/var/run/docker.sock -v $JENKINS_HOME:/var/jenkins_home -p 8080:8080 -p 50000:50000 jenkins_img'