#!/usr/bin/env python
# coding: utf-8

''' 
  CSS Knife Sorts your CSS
'''


import sys

import tinycss

def ignore_leading_dot(item):
    if item['selector'].startswith('.'):
        return item['selector'][1:]
    else:
        return item['selector']


def style_errors(errors):
  if errors:
    print 'Your stylesheet has the following errors:'
    for e in errors:
      print '+ {}'.format(e)

def print_sorted_list(r_list):
  for rule in r_list:
    print '%s {' % (rule['selector'])
    for dec in rule['declarations']:
      for k,v in dec.iteritems():
        print '    %s: %s;' % (k,v)
    print '}\n'

if len(sys.argv) < 2:
  print 'no file argument'
  sys.exit(1)
else:
  css_file = sys.argv[1]

try:
  parser = tinycss.make_parser()
  ss = parser.parse_stylesheet_file(css_file)
except IOError:
  print 'Could not open file %' % (css_file)
  sys.exit(1)


if ss.errors:
  style_errors(ss.errors)
  sys.exit(1)

app = {}
app['rules'] = []

for rule in ss.rules:
  d = dict()
  d['selector'] = rule.selector.as_css()
  d['declarations'] = []
  for dec in rule.declarations:
    d['declarations'].append({dec.name: dec.value.as_css()})
  app['rules'].append(d)

# sort inner declarations
for rule in app['rules']:
  rule['declarations'].sort(key=lambda x: x.keys())

# sort selector blocks
app['rules'].sort(key=ignore_leading_dot)

print_sorted_list(app['rules'])
