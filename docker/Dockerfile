#
# JSON Model Compiler Multi-Language Environment
#
FROM ubuntu:24.04
LABEL description="JSON Model Compiler"
ARG JMC=main
ARG JSU=main

# system update, installs, cleanup
RUN apt update ; \
    apt upgrade -y ; \
    apt install -y --no-install-recommends --fix-missing \
        git ca-certificates libtool m4 time automake make pkgconf gcc g++ clang-20 \
        texinfo jq curl less \
        nano vim libpcre2-dev libre2-dev libjansson-dev \
        python3 python-is-python3 python3-venv python3-pip \
        perl libre-engine-re2-perl libjson-maybexs-perl libcpanel-json-xs-perl libdatetime-hires-perl \
        openjdk-21-jdk openjdk-21-jre default-jdk libgetopt-java maven \
        locales ; \
    apt clean

# set unicode
RUN locale-gen C.UTF-8
ENV LANG=C.UTF-8

# application directory
RUN mkdir /app
WORKDIR /app

# compile cre2 into /usr/local
RUN git clone https://github.com/marcomaggi/cre2.git
RUN cd cre2 ; \
    sh autogen.sh ; \
    ./configure --enable-maintainer-mode ; \
    make ; \
    make install ; \
    cd .. ; \
    rm -rf cre2
ENV LD_LIBRARY_PATH=/usr/local/lib

# setup python environment, native pip complains about direct installations otherwise
RUN python -m venv venv ; \
    venv/bin/pip install -U pip ; \
    venv/bin/pip install pytest pytest-xdist[psutils] filelock
ENV PATH=/app/venv/bin:$PATH

# nodejs >= 20.0.0
ENV NVM_DIR=/usr/local/nvm
RUN mkdir -p $NVM_DIR
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
RUN . $NVM_DIR/nvm.sh && \
	nvm install stable && \
    nvm alias default stable && \
    nvm use default
RUN ln -s $NVM_DIR/versions/node/v* $NVM_DIR/versions/node/stable
# NOTE NODE_PATH is ignored by "import" on node :-/
ENV NODE_PATH=/app/node_modules
ENV PATH=$NVM_DIR/versions/node/stable/bin:$PATH

# js runtime
RUN echo '{"name":"zx80-jmc","type":"module"}' | jq > package.json
RUN npm install re2

# actual application stuff
# direct install json-model and json-schema-utils from github
# pip install json-model-compiler json-schema-utils
# npm install json_model_runtime

RUN git clone -b $JMC https://github.com/clairey-zx81/json-model.git
RUN /app/venv/bin/pip install -e ./json-model
RUN npm install file:./json-model/json_model/runtime/js
# RUN ls -la node_modules
# RUN rm -rf ./json-model  # no, editable

RUN git clone -b $JSU https://github.com/zx80/json-schema-utils.git
RUN /app/venv/bin/pip install -e ./json-schema-utils
# RUN rm -rf ./json-schema-utils  # no, editable

# java runtime, direct download with hardcoded version
ENV java=/app/json-model/json_model/runtime/java
ENV gson=2.13.2
ENV jackson=2.20.0
ENV jackson_ann=2.20
ENV jakarta=2.1.3
ENV johnzon=2.0.2
RUN for artifact in \
        com.google.code.gson:gson:$gson \
        com.fasterxml.jackson.core:jackson-core:$jackson \
        com.fasterxml.jackson.core:jackson-databind:$jackson \
        com.fasterxml.jackson.core:jackson-annotations:$jackson_ann \
        jakarta.json:jakarta.json-api:$jakarta \
        org.apache.johnzon:johnzon-core:$johnzon \
        ; \
    do \
        mvn dependency:copy -Dartifact=$artifact -DoutputDirectory=$java ; \
    done
ENV CLASSPATH=.:/app/workspace:/app/workspace/java:/app/workspace/tmp
ENV CLASSPATH=$CLASSPATH:$java/json-model.jar
ENV CLASSPATH=$CLASSPATH:/usr/share/java/gnu-getopt.jar
ENV CLASSPATH=$CLASSPATH:$java/gson-$gson.jar
ENV CLASSPATH=$CLASSPATH:$java/jackson-core-$jackson.jar:$java/jackson-databind-$jackson.jar:$java/jackson-annotations-$jackson_ann.jar
ENV CLASSPATH=$CLASSPATH:$java/jakarta.json-api-$jakarta.jar:$java/johnzon-core-$johnzon.jar
RUN make -C $java jar

# convenient shell and vi environment
RUN echo "# reset default prompt\nexport PS1='zx80/jmc> '" >> /etc/bash.bashrc
RUN echo "syntax on\nset expandtab\nset tabstop=4\nset shiftwidth=4\nset ruler" >> /etc/vim/vimrc.local

# fix perms to allow any uid to read/write
RUN find /app -type d -print | xargs chmod a+rwx
RUN find /app -type f -print | xargs chmod a+rw

# setup docker entry point and utils
RUN mkdir /app/workspace
WORKDIR /app/workspace
ENV TMPDIR=/tmp
ENV JSON_MODEL_CACHEDIR=/tmp
ENV PERLLIB=/app/json-model/json_model/runtime/pl/lib
ENV PATH=$PATH:.
ENTRYPOINT ["/app/venv/bin/jmc"]
