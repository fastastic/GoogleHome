#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import sys
import requests

###### SSH monitoring ######

user = ""
ip = ""

while(1):
	with open('/var/log/auth.log', 'r') as f:
    		lines = f.read().splitlines()
    		
		#Falla aquí porque a veces el fichero está vacío
		if len(lines) > 0:
			last_line = lines[-1]

			last_line = last_line.split()

			if "sshd" and "Accepted" in last_line:
				print last_line
				user = last_line[8]
				ip = last_line[10]
				print user, ip

				# Realizamos la petición POST
				msg = "Se ha realizado una conexión al servidor SSH desde la dirección " + ip + " con el usuario " + user
				r = requests.post('http://192.168.1.139:1880/post', data = {'message': msg})
