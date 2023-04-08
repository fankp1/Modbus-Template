
# linux-driver-modbus 

## System requirements

Has to be done once during installation of the system. It disables and stops the terminal daemon blocking ttyS2:

```bash
rm /lib/systemd/system/serial-getty@.service
rm -r /lib/systemd/system/serial-getty@.service.d
```

Has to be done every time the system starts up!!
`(currently done in the uservice, because its running as root anyway)`.

This exports the r/w pin of the modbus in sysfs and gives rights to gpio group `(needs root privileges!)`

```bash
echo 131 > /sys/class/gpio/export
chown root:gpio /sys/class/gpio/gpio131/*
chmod g+w /sys/class/gpio/gpio131/*
```

Don't forget to add the user which executes the uService to the group gpio!!


## Build & run for dev and testing

- To test the binaries manually:

  ```bash
  make
  ```


```
