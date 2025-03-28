#!/bin/sh


for yaml in airquality \
 boiler \
 desk \
 livingroom \
 loftbed \
 porchdisplay \
 printmonitor \
 printmonitor2 \
 watersoftener \
 cupboard
do
  esphome compile $yaml.yaml && esphome upload --device ${yaml}.iot.cns.me $yaml.yaml
done
