#!/usr/bin/env python 
# coding: utf-8

''' 
  CSS Knife
  Usage: knife.py file 
'''

import sys
import tinycss

def usage():
  usage_string = ''' 
  Usage: knife.py file.css 
  '''
  print usage_string

def ignore_leading_char(item,excluded_chars=".#"):
  if item['selector'][0] in excluded_chars:
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
    print "{} {{".format(rule['selector'])
    for dec in rule['declarations']:
      for k,v in dec.iteritems():
        print "\t{}: {};".format(k,v)
    print '}\n'

def main():

  if len(sys.argv) < 2:
    usage()
    sys.exit(1)
  else:
    css_file = sys.argv[1]

  try:
    parser = tinycss.make_parser()
    ss = parser.parse_stylesheet_file(css_file)
  except IOError:
    print "Could not open file {}".format(css_file)
    sys.exit(1)


  if ss.errors:
    style_errors(ss.errors)
    sys.exit(1)

  knife = {}
  knife['rules'] = []

  for rule in ss.rules:
    d = dict()
    d['selector'] = rule.selector.as_css()
    d['declarations'] = []
    for dec in rule.declarations:
      d['declarations'].append({dec.name: dec.value.as_css()})
    knife['rules'].append(d)

  # sort inner declarations
  for rule in knife['rules']:
    rule['declarations'].sort(key=lambda x: x.keys())

  # sort selector blocks
  knife['rules'].sort(key=ignore_leading_char)

  print_sorted_list(knife['rules'])

if __name__ == "__main__":
  main()
