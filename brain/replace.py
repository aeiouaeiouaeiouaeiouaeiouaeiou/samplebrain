#!/usr/bin/env python
import re
import sys

fn = sys.argv[1]

test = open(fn, 'r').read()

pattern = re.compile('[A-Z](?=[a-z])')

def format_term(term):
    return '_%s' % (term.lower())

test = pattern.sub(lambda m: format_term(m.group(0)), test)

test = re.sub(r'(?<=[^a-z])_(?=[a-z])','',test)

o = open(fn,'w')
o.write(test)
o.close()
