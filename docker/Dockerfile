FROM ubuntu:24.04
LABEL description="JSON Model Compiler"

# system update, installs, cleanup
RUN apt update ; \
    apt upgrade -y ; \
    apt install -y --no-install-recommends --fix-missing \
	    adduser \
        vim git ca-certificates libtool m4 time automake make pkgconf gcc g++ texinfo jq curl \
        libpcre2-dev libre2-dev libjansson-dev \
        python3 python-is-python3 python3-venv python3-pip ; \
    apt clean

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
    venv/bin/pip install -U pip

# nodejs >= 20.0.0
ENV NVM_DIR=/usr/local/nvm
RUN mkdir -p $NVM_DIR
RUN curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.40.3/install.sh | bash
RUN . $NVM_DIR/nvm.sh && \
	nvm install stable && \
    nvm alias default stable && \
    nvm use default
RUN ln -s $NVM_DIR/versions/node/v* $NVM_DIR/versions/node/stable
ENV NODE_PATH=/app/node_modules
ENV PATH=$NVM_DIR/versions/node/stable/bin:$PATH

# js runtime
RUN echo '{"name":"jmc-benchmark","type":"module"}' | jq > package.json
RUN npm install re2

# actual application stuff
# direct install json-model and json-schema-utils from github
# pip install json-model-compiler json-schema-utils
# npm install json_model_runtime

RUN git clone https://github.com/clairey-zx81/json-model.git
RUN /app/venv/bin/pip install -e ./json-model
RUN npm install file:./json-model/js_runtime
# RUN rm -rf ./json-model  # not if editable

RUN git clone https://github.com/zx80/json-schema-utils.git
RUN /app/venv/bin/pip install -e ./json-schema-utils
# RUN rm -rf ./json-schema-utils

# setup docker entry point and utils
RUN mkdir /workspace
WORKDIR /workspace
ENV JSON_MODEL_CACHEDIR=/tmp
ENTRYPOINT ["/app/venv/bin/jmc"]
