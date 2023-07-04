#!/bin/sh


for yaml in airquality boiler desk freyaclock garageopener loftbed noahclock porchdisplay
do
  esphome compile $yaml.yaml && esphome upload $yaml.yaml
done
