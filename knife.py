#!/usr/bin/env python
# coding: utf-8

# NOTE TO AUTHOR: remember to run . /data/python/env/bin/activate 

# 
#   CSS Knife - sorts your CSS
#
#   hard dependencies: tinycss
#

import sys

import tinycss

if len(sys.argv) < 2:
  print 'no file argument'
  sys.exit(1)

# parse stylesheet file into object form
parser = tinycss.make_parser()
ss = parser.parse_stylesheet_file(sys.argv[1])
if ss.errors:
  print '\n'.join(['** your stylesheet has errors **',ss.errors,''])
  print ss.errors
  print '\n'

# copy what I need from the ss object into dict below

#  rule dict example
#  {'selector':'li p',
#     'declarations' : 
#           [
#               {'background':'red'},
#               {'width': '400px'}
#           ] 
#  }

# first copy out of parsed ss object
my_rule_list = []
for rule in ss.rules:
  d = dict()
  d['selector'] = rule.selector.as_css()
  d['declarations'] = []
  for dec in rule.declarations:
    # appending declaration {'name':'value'}
    d['declarations'].append({dec.name : dec.value.as_css()})
  my_rule_list.append(d)

# copy rule list 
rules_sorted_by_declaration = my_rule_list[:]

# sort list of declarations in-place
for rule in rules_sorted_by_declaration:
  rule['declarations'].sort(key=lambda x: x.keys())

# sort rules, too
rules_sorted_by_selector_and_declaration = sorted(rules_sorted_by_declaration, key=lambda x: x['selector'])

def print_sorted_list(r_list):
  for rule in r_list:
    print '%s {' % (rule['selector'])
    for dec in rule['declarations']:
      for k,v in dec.iteritems():
        print '    %s: %s;' % (k,v)
    print '}\n'

print_sorted_list(rules_sorted_by_selector_and_declaration)
