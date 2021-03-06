// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "jdb_kern_info.h"
#include "jdb_kern_info_i.h"

#line 11 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"

static Jdb_kern_info_pci k_P INIT_PRIORITY(JDB_MODULE_INIT_PRIO+1);

#line 13 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"


Jdb_kern_info_pci::Jdb_kern_info_pci()
  : Jdb_kern_info_module('P', "PCI devices")
{
  Jdb_kern_info::register_subcmd(this);
}

#line 20 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/jdb/ia32/jdb_kern_info-pci.cpp"


void
Jdb_kern_info_pci::show()
{
  static const char * const classes[] =
    { "unknown", "mass storage contoller", "network controller", 
      "display controller", "multimedia device", "memory controller",
      "bridge device", "simple communication controller", 
      "system peripheral", "input device", "docking station", 
      "processor", "serial bus controller", "wireless controller",
      "intelligent I/O controller", "satellite communication controller",
      "encryption/decryption controller", 
      "data aquisition/signal processing controller" };
  Mword bus, buses, dev, subdev, subdevs;

  for (bus = 0, buses = 1; bus < buses; bus++)
    {
      for (dev = 0; dev < 32; dev++)
        {
          Pci::Cfg_addr _device(bus, dev);

          Unsigned8 hdr_type; Pci::read_cfg(_device + 0x0E, &hdr_type);
          subdevs = (hdr_type & 0x80) ? 8 : 1;

          for (subdev = 0; subdev < subdevs; subdev++)
            {
              _device.func(subdev);
              Unsigned16 vendor; Pci::read_cfg(_device + 0x00, &vendor);
              Unsigned16 device; Pci::read_cfg(_device + 0x02, &device);

              if ((vendor == 0xffff && device == 0xffff) ||
                  (device == 0x0000 && device == 0x0000))
                break;

              Unsigned8 classcode; Pci::read_cfg(_device + 0x0b, &classcode);
              Unsigned8 subclass;  Pci::read_cfg(_device + 0x0a, &subclass);

              if (classcode == 0x06 && subclass == 0x04)
                buses++;

              printf("%02lx:%02lx.%1lx Class %02x%02x: %04x:%04x ",
                     bus, dev, subdev, (unsigned)classcode,
                     (unsigned)subclass, (unsigned)device, (unsigned)vendor);
              if (classcode < sizeof(classes)/sizeof(classes[0]))
                printf("%s", classes[classcode]);
              putchar('\n');
            }
        }
    }
}
