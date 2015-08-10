CONFIG += ordered

TEMPLATE = subdirs

SUBDIRS += $$PWD/src \
           $$PWD/examples

examples.depends = $$PWD/src
