#
# JSON Model Compiler Multi-Language Environment
#
FROM ubuntu:24.04
LABEL description="JSON Model Compiler"

# system update, installs, cleanup
RUN apt update ; \
    apt upgrade -y ; \
    apt install -y --no-install-recommends --fix-missing \
        git ca-certificates libtool m4 time automake make pkgconf gcc g++ texinfo jq curl less \
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

RUN git clone https://github.com/clairey-zx81/json-model.git
RUN /app/venv/bin/pip install -e ./json-model
RUN npm install file:./json-model/json_model/runtime/js
RUN ls -la node_modules
# RUN rm -rf ./json-model  # not if editable (-e above)

RUN git clone https://github.com/zx80/json-schema-utils.git
RUN /app/venv/bin/pip install -e ./json-schema-utils
# RUN rm -rf ./json-schema-utils

# java runtime, direct download with hardcoded version
ENV java=/app/json-model/json_model/runtime/java
RUN for artifact in \
        com.google.code.gson:gson:2.13.1 \
        com.fasterxml.jackson.core:jackson-core:2.19.2 \
        com.fasterxml.jackson.core:jackson-databind:2.19.2 \
        com.fasterxml.jackson.core:jackson-annotations:2.19.2 \
        jakarta.json:jakarta.json-api:2.0.2 \
        org.apache.johnzon:johnzon-core:2.0.2 \
        ; \
    do \
        mvn dependency:copy -Dartifact=$artifact -DoutputDirectory=$java ; \
    done
ENV CLASSPATH=.:/app/workspace:/usr/share/java/gnu-getopt.jar:$java/json-model.jar:$java/gson-2.13.1.jar:$java/jackson-core-2.19.2.jar:$java/jackson-databind-2.19.2.jar:$java/jackson-annotations-2.19.2.jar:$java/jakarta.json-api-2.0.2.jar:$java/johnzon-core-2.0.2.jar
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
ENV PERLLIB=/app/json-model/json_model/runtime/pl
ENV PATH=$PATH:.
ENTRYPOINT ["/app/venv/bin/jmc"]
