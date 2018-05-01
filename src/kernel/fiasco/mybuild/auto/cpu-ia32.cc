// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#include "cpu.h"
#include "cpu_i.h"

#line 322 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

DEFINE_PER_CPU_P(0) Per_cpu<Cpu> Cpu::cpus(Per_cpu_data::Cpu_num);
#line 324 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"
Cpu *Cpu::_boot_cpu;
#line 325 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


Cpu::Vendor_table const Cpu::intel_table[] FIASCO_INITDATA_CPU =
{
  { 0xf0fF0, 0x00400, 0xFFFF, "i486 DX-25/33"                   },
  { 0xf0fF0, 0x00410, 0xFFFF, "i486 DX-50"                      },
  { 0xf0fF0, 0x00420, 0xFFFF, "i486 SX"                         },
  { 0xf0fF0, 0x00430, 0xFFFF, "i486 DX/2"                       },
  { 0xf0fF0, 0x00440, 0xFFFF, "i486 SL"                         },
  { 0xf0fF0, 0x00450, 0xFFFF, "i486 SX/2"                       },
  { 0xf0fF0, 0x00470, 0xFFFF, "i486 DX/2-WB"                    },
  { 0xf0fF0, 0x00480, 0xFFFF, "i486 DX/4"                       },
  { 0xf0fF0, 0x00490, 0xFFFF, "i486 DX/4-WB"                    },
  { 0xf0fF0, 0x00500, 0xFFFF, "Pentium A-Step"                  },
  { 0xf0fF0, 0x00510, 0xFFFF, "Pentium P5"                      },
  { 0xf0fF0, 0x00520, 0xFFFF, "Pentium P54C"                    },
  { 0xf0fF0, 0x00530, 0xFFFF, "Pentium P24T Overdrive"          },
  { 0xf0fF0, 0x00540, 0xFFFF, "Pentium P55C MMX"                },
  { 0xf0fF0, 0x00570, 0xFFFF, "Pentium Mobile"                  },
  { 0xf0fF0, 0x00580, 0xFFFF, "Pentium MMX Mobile (Tillamook)"  },
  { 0xf0fF0, 0x00600, 0xFFFF, "Pentium-Pro A-Step"              },
  { 0xf0fF0, 0x00610, 0xFFFF, "Pentium-Pro"                     },
  { 0xf0fF0, 0x00630, 512,    "Pentium II (Klamath)"            },
  { 0xf0fF0, 0x00640, 512,    "Pentium II (Deschutes)"          },
  { 0xf0fF0, 0x00650, 1024,   "Pentium II (Drake)"              },
  { 0xf0fF0, 0x00650, 512,    "Pentium II (Deschutes)"          },
  { 0xf0fF0, 0x00650, 256,    "Pentium II Mobile (Dixon)"       },
  { 0xf0fF0, 0x00650, 0,      "Celeron (Covington)"             },
  { 0xf0fF0, 0x00660, 128,    "Celeron (Mendocino)"             },
  { 0xf0fF0, 0x00670, 1024,   "Pentium III (Tanner)"            },
  { 0xf0fF0, 0x00670, 512,    "Pentium III (Katmai)"            },
  { 0xf0fF0, 0x00680, 256,    "Pentium III (Coppermine)"        },
  { 0xf0fF0, 0x00680, 128,    "Celeron (Coppermine)"            },
  { 0xf0fF0, 0x00690, 1024,   "Pentium-M (Banias)"              },
  { 0xf0fF0, 0x00690, 512,    "Celeron-M (Banias)"              },
  { 0xf0fF0, 0x006a0, 1024,   "Pentium III (Cascades)"          },
  { 0xf0fF0, 0x006b0, 512,    "Pentium III-S"                   },
  { 0xf0fF0, 0x006b0, 256,    "Pentium III (Tualatin)"          },
  { 0xf0fF0, 0x006d0, 2048,   "Pentium-M (Dothan)"              },
  { 0xf0fF0, 0x006d0, 1024,   "Celeron-M (Dothan)"              },
  { 0xf0fF0, 0x006e0, 2048,   "Core (Yonah)"                    },
  { 0xf0fF0, 0x006f0, 2048,   "Core 2 (Merom)"                  },
  { 0xf0f00, 0x00700, 0xFFFF, "Itanium (Merced)"                },
  { 0xf0fF0, 0x00f00, 256,    "Pentium 4 (Willamette/Foster)"   },
  { 0xf0fF0, 0x00f10, 256,    "Pentium 4 (Willamette/Foster)"   },
  { 0xf0fF0, 0x00f10, 128,    "Celeron (Willamette)"            },
  { 0xf0fF0, 0x00f20, 512,    "Pentium 4 (Northwood/Prestonia)" },
  { 0xf0fF0, 0x00f20, 128,    "Celeron (Northwood)"             },
  { 0xf0fF0, 0x00f30, 1024,   "Pentium 4E (Prescott/Nocona)"    },
  { 0xf0fF0, 0x00f30, 256,    "Celeron D (Prescott)"            },
  { 0xf0fF4, 0x00f40, 1024,   "Pentium 4E (Prescott/Nocona)"    },
  { 0xf0fF4, 0x00f44, 1024,   "Pentium D (Smithfield)"          },
  { 0xf0fF0, 0x00f40, 256,    "Celeron D (Prescott)"            },
  { 0xf0fF0, 0x00f60, 2048,   "Pentium D (Cedarmill/Presler)"   },
  { 0xf0fF0, 0x00f60, 512,    "Celeron D (Cedarmill)"           },
  { 0xf0ff0, 0x10600,   0,    "Celeron, 65nm"                   },
  { 0xf0ff0, 0x10670, 2048,   "Core2 / Xeon (Wolfdale), 45nm"   },
  { 0xf0ff0, 0x106a0, 0xffff, "Core i7 / Xeon, 45nm"            },
  { 0xf0ff0, 0x106b0, 0xffff, "Xeon MP, 45nm"                   },
  { 0xf0ff0, 0x106c0, 0xffff, "Atom"                            },
  { 0x0,     0x0,     0xFFFF, ""                                }
};
#line 387 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::amd_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x430, 0xFFFF, "Am486DX2-WT"                     },
  { 0xFF0, 0x470, 0xFFFF, "Am486DX2-WB"                     },
  { 0xFF0, 0x480, 0xFFFF, "Am486DX4-WT / Am5x86-WT"         },
  { 0xFF0, 0x490, 0xFFFF, "Am486DX4-WB / Am5x86-WB"         },
  { 0xFF0, 0x4a0, 0xFFFF, "SC400"                           },
  { 0xFF0, 0x4e0, 0xFFFF, "Am5x86-WT"                       },
  { 0xFF0, 0x4f0, 0xFFFF, "Am5x86-WB"                       },
  { 0xFF0, 0x500, 0xFFFF, "K5 (SSA/5) PR75/90/100"          },
  { 0xFF0, 0x510, 0xFFFF, "K5 (Godot) PR120/133"            },
  { 0xFF0, 0x520, 0xFFFF, "K5 (Godot) PR150/166"            },
  { 0xFF0, 0x530, 0xFFFF, "K5 (Godot) PR200"                },
  { 0xFF0, 0x560, 0xFFFF, "K6 (Little Foot)"                },
  { 0xFF0, 0x570, 0xFFFF, "K6 (Little Foot)"                },
  { 0xFF0, 0x580, 0xFFFF, "K6-II (Chomper)"                 },
  { 0xFF0, 0x590, 256,    "K6-III (Sharptooth)"             },
  { 0xFF0, 0x5c0, 128,    "K6-2+"                           },
  { 0xFF0, 0x5d0, 256,    "K6-3+"                           },
  { 0xFF0, 0x600, 0xFFFF, "Athlon K7 (Argon)"               },
  { 0xFF0, 0x610, 0xFFFF, "Athlon K7 (Pluto)"               },
  { 0xFF0, 0x620, 0xFFFF, "Athlon K75 (Orion)"              },
  { 0xFF0, 0x630, 64,     "Duron (Spitfire)"                },
  { 0xFF0, 0x640, 256,    "Athlon (Thunderbird)"            },
  { 0xFF0, 0x660, 256,    "Athlon (Palomino)"               },
  { 0xFF0, 0x660, 64,     "Duron (Morgan)"                  },
  { 0xFF0, 0x670, 64,     "Duron (Morgan)"                  },
  { 0xFF0, 0x680, 256,    "Athlon (Thoroughbred)"           },
  { 0xFF0, 0x680, 64,     "Duron (Applebred)"               },
  { 0xFF0, 0x6A0, 512,    "Athlon (Barton)"                 },
  { 0xFF0, 0x6A0, 256,    "Athlon (Thorton)"                },
  { 0xfff0ff0,  0x000f00,   0,      "Athlon 64 (Clawhammer)"       },
  { 0xfff0ff0,  0x000f10,   0,      "Opteron (Sledgehammer)"       },
  { 0xfff0ff0,  0x000f40,   0,      "Athlon 64 (Clawhammer)"       },
  { 0xfff0ff0,  0x000f50,   0,      "Opteron (Sledgehammer)"       },
  { 0xfff0ff0,  0x000fc0,   512,    "Athlon64 (Newcastle)"         },
  { 0xfff0ff0,  0x000fc0,   256,    "Sempron (Paris)"              },
  { 0xfff0ff0,  0x010f50,   0,      "Opteron (Sledgehammer)"       },
  { 0xfff0ff0,  0x010fc0,   0,      "Sempron (Oakville)"           },
  { 0xfff0ff0,  0x010ff0,   0,      "Athlon 64 (Winchester)"       },
  { 0xfff0ff0,  0x020f10,   0,      "Opteron (Jackhammer)"         },
  { 0xfff0ff0,  0x020f30,   0,      "Athlon 64 X2 (Toledo)"        },
  { 0xfff0ff0,  0x020f40,   0,      "Turion 64 (Lancaster)"        },
  { 0xfff0ff0,  0x020f50,   0,      "Opteron (Venus)"              },
  { 0xfff0ff0,  0x020f70,   0,      "Athlon 64 (San Diego)"        },
  { 0xfff0ff0,  0x020fb0,   0,      "Athlon 64 X2 (Manchester)"    },
  { 0xfff0ff0,  0x020fc0,   0,      "Sempron (Palermo)"            },
  { 0xfff0ff0,  0x020ff0,   0,      "Athlon 64 (Venice)"           },
  { 0xfff0ff0,  0x040f10,   0,      "Opteron (Santa Rosa)"         },
  { 0xfff0ff0,  0x040f30,   0,      "Athlon 64 X2 (Windsor)"       },
  { 0xfff0ff0,  0x040f80,   0,      "Turion 64 X2 (Taylor)"        },
  { 0xfff0ff0,  0x060fb0,   0,      "Athlon 64 X2 (Brisbane)"      },
  { 0x0,        0x0,        0,      ""                             }
};
#line 442 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::cyrix_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x440, 0xFFFF, "Gx86 (Media GX)"                 },
  { 0xFF0, 0x490, 0xFFFF, "5x86"                            },
  { 0xFF0, 0x520, 0xFFFF, "6x86 (M1)"                       },
  { 0xFF0, 0x540, 0xFFFF, "GXm"                             },
  { 0xFF0, 0x600, 0xFFFF, "6x86MX (M2)"                     },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 452 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::via_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x540, 0xFFFF, "IDT Winchip C6"                  },
  { 0xFF0, 0x580, 0xFFFF, "IDT Winchip 2A/B"                },
  { 0xFF0, 0x590, 0xFFFF, "IDT Winchip 3"                   },
  { 0xFF0, 0x650, 0xFFFF, "Via Jalapeno (Joshua)"           },
  { 0xFF0, 0x660, 0xFFFF, "Via C5A (Samuel)"                },
  { 0xFF8, 0x670, 0xFFFF, "Via C5B (Samuel 2)"              },
  { 0xFF8, 0x678, 0xFFFF, "Via C5C (Ezra)"                  },
  { 0xFF0, 0x680, 0xFFFF, "Via C5N (Ezra-T)"                },
  { 0xFF0, 0x690, 0xFFFF, "Via C5P (Nehemiah)"              },
  { 0xFF0, 0x6a0, 0xFFFF, "Via C5J (Esther)"                },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 467 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::umc_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x410, 0xFFFF, "U5D"                             },
  { 0xFF0, 0x420, 0xFFFF, "U5S"                             },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 474 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::nexgen_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x500, 0xFFFF, "Nx586"                           },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 480 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::rise_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x500, 0xFFFF, "mP6 (iDragon)"                   },
  { 0xFF0, 0x520, 0xFFFF, "mP6 (iDragon)"                   },
  { 0xFF0, 0x580, 0xFFFF, "mP6 (iDragon II)"                },
  { 0xFF0, 0x590, 0xFFFF, "mP6 (iDragon II)"                },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 489 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::transmeta_table[] FIASCO_INITDATA_CPU =
{
  { 0xFFF, 0x542, 0xFFFF, "TM3x00 (Crusoe)"                 },
  { 0xFFF, 0x543, 0xFFFF, "TM5x00 (Crusoe)"                 },
  { 0xFF0, 0xf20, 0xFFFF, "TM8x00 (Efficeon)"               },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 497 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::sis_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x500, 0xFFFF, "55x"                             },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 503 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const Cpu::nsc_table[] FIASCO_INITDATA_CPU =
{
  { 0xFF0, 0x540, 0xFFFF, "Geode GX1"                       },
  { 0xFF0, 0x550, 0xFFFF, "Geode GX2"                       },
  { 0xFF0, 0x680, 0xFFFF, "Geode NX"                        },
  { 0x0,   0x0,   0xFFFF, ""                                }
};
#line 511 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Cache_table const Cpu::intel_cache_table[] FIASCO_INITDATA_CPU =
{
  { 0x01, Tlb_inst_4k,        32,   4,    0 },
  { 0x02, Tlb_inst_4M,         2,   4,    0 },
  { 0x03, Tlb_data_4k,        64,   4,    0 },
  { 0x04, Tlb_data_4M,         8,   4,    0 },
  { 0x05, Tlb_data_4M,        32,   4,    0 },
  { 0x06, Cache_l1_inst,       8,   4,   32 },
  { 0x08, Cache_l1_inst,      16,   4,   32 },
  { 0x09, Cache_l1_inst,      32,   4,   64 },
  { 0x0A, Cache_l1_data,       8,   2,   32 },
  { 0x0B, Tlb_inst_4M,         4,   4,    0 },
  { 0x0C, Cache_l1_data,      16,   4,   32 },
  { 0x0D, Cache_l1_data,      16,   4,   64 },
  { 0x0E, Cache_l1_data,      24,   6,   64 },
  { 0x21, Cache_l2,          256,   8,   64 },
  { 0x22, Cache_l3,          512,   4,   64 },  /* sectored */
  { 0x23, Cache_l3,         1024,   8,   64 },  /* sectored */
  { 0x25, Cache_l3,         2048,   8,   64 },  /* sectored */
  { 0x29, Cache_l3,         4096,   8,   64 },  /* sectored */
  { 0x2C, Cache_l1_data,      32,   8,   64 },
  { 0x30, Cache_l1_inst,      32,   8,   64 },
  { 0x39, Cache_l2,          128,   4,   64 },  /* sectored */
  { 0x3B, Cache_l2,          128,   2,   64 },  /* sectored */
  { 0x3C, Cache_l2,          256,   4,   64 },  /* sectored */
  { 0x41, Cache_l2,          128,   4,   32 },
  { 0x42, Cache_l2,          256,   4,   32 },
  { 0x43, Cache_l2,          512,   4,   32 },
  { 0x44, Cache_l2,         1024,   4,   32 },
  { 0x45, Cache_l2,         2048,   4,   32 },
  { 0x46, Cache_l3,         4096,   4,   64 },
  { 0x47, Cache_l3,         8192,   8,   64 },
  { 0x48, Cache_l2,         3072,  12,   64 },
  { 0x49, Cache_l2,         4096,  16,   64 },
  { 0x4A, Cache_l3,         6144,  12,   64 },
  { 0x4B, Cache_l3,         8192,  16,   64 },
  { 0x4C, Cache_l3,        12288,  12,   64 },
  { 0x4D, Cache_l3,        16384,  16,   64 },
  { 0x4E, Cache_l3,         6144,  24,   64 },
  { 0x4F, Tlb_inst_4k,        32,   0,    0 },
  { 0x50, Tlb_inst_4k_4M,     64,   0,    0 },
  { 0x51, Tlb_inst_4k_4M,    128,   0,    0 },
  { 0x52, Tlb_inst_4k_4M,    256,   0,    0 },
  { 0x56, Tlb_data_4M,        16,   4,    0 },
  { 0x57, Tlb_data_4k,        16,   4,    0 },
  { 0x59, Tlb_data_4k,        16,   0,    0 },
  { 0x5A, Tlb_data_2M_4M,     32,   4,    0 },
  { 0x5B, Tlb_data_4k_4M,     64,   0,    0 },
  { 0x5C, Tlb_data_4k_4M,    128,   0,    0 },
  { 0x5D, Tlb_data_4k_4M,    256,   0,    0 },
  { 0x60, Cache_l1_data,      16,   8,   64 },
  { 0x66, Cache_l1_data,       8,   4,   64 },  /* sectored */
  { 0x67, Cache_l1_data,      16,   4,   64 },  /* sectored */
  { 0x68, Cache_l1_data,      32,   4,   64 },  /* sectored */
  { 0x70, Cache_l1_trace,     12,   8,    0 },
  { 0x71, Cache_l1_trace,     16,   8,    0 },
  { 0x72, Cache_l1_trace,     32,   8,    0 },
  { 0x77, Cache_l1_inst,      16,   4,   64 },
  { 0x78, Cache_l2,         1024,   4,   64 },
  { 0x79, Cache_l2,          128,   8,   64 },  /* sectored */
  { 0x7A, Cache_l2,          256,   8,   64 },  /* sectored */
  { 0x7B, Cache_l2,          512,   8,   64 },  /* sectored */
  { 0x7C, Cache_l2,         1024,   8,   64 },  /* sectored */
  { 0x7D, Cache_l2,         2048,   8,   64 },
  { 0x7E, Cache_l2,          256,   8,  128 },
  { 0x7F, Cache_l2,          512,   2,   64 },
  { 0x80, Cache_l2,          512,  16,   64 },
  { 0x82, Cache_l2,          256,   8,   32 },
  { 0x83, Cache_l2,          512,   8,   32 },
  { 0x84, Cache_l2,         1024,   8,   32 },
  { 0x85, Cache_l2,         2048,   8,   32 },
  { 0x86, Cache_l2,          512,   4,   64 },
  { 0x87, Cache_l2,         1024,   8,   64 },
  { 0x8D, Cache_l3,         3072,  12,  128 },
  { 0xB0, Tlb_inst_4k,       128,   4,    0 },
  { 0xB3, Tlb_data_4k,       128,   4,    0 },
  { 0xB4, Tlb_data_4k,       256,   4,    0 },
  { 0xBA, Tlb_data_4k,        64,   4,    0 },
  { 0xC0, Tlb_data_4k_4M,      8,   4,    0 },
  { 0xCA, Tlb_data_4k_4M,    512,   4,    0 },
  { 0xD0, Cache_l3,          512,   4,   64 },
  { 0xD1, Cache_l3,         1024,   4,   64 },
  { 0xD2, Cache_l3,         2048,   4,   64 },
  { 0xD6, Cache_l3,         1024,   8,   64 },
  { 0xD7, Cache_l3,         2048,   8,   64 },
  { 0xD8, Cache_l3,         4096,   8,   64 },
  { 0xDC, Cache_l3,         1536,  12,   64 },
  { 0xDD, Cache_l3,         3072,  12,   64 },
  { 0xDE, Cache_l3,         6144,  12,   64 },
  { 0xE2, Cache_l3,         2048,  16,   64 },
  { 0xE3, Cache_l3,         4096,  16,   64 },
  { 0xE4, Cache_l3,         8192,  16,   64 },
  { 0xEA, Cache_l3,        12288,  24,   64 },
  { 0xEB, Cache_l3,        18432,  24,   64 },
  { 0xEC, Cache_l3,        24576,  24,   64 },
  { 0x0,  Cache_unknown,       0,   0,    0 }
};
#line 609 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

char const * const Cpu::vendor_ident[] =
{
   0,
  "GenuineIntel",
  "AuthenticAMD",
  "CyrixInstead",
  "CentaurHauls",
  "UMC UMC UMC ",
  "NexGenDriven",
  "RiseRiseRise",
  "GenuineTMx86",
  "SiS SiS SiS ",
  "Geode by NSC"
};
#line 624 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

Cpu::Vendor_table const * const Cpu::vendor_table[] =
{
  0,
  intel_table,
  amd_table,
  cyrix_table,
  via_table,
  umc_table,
  nexgen_table,
  rise_table,
  transmeta_table,
  sis_table,
  nsc_table
};
#line 639 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

char const * const Cpu::exception_strings[] =
{
  /*  0 */ "Divide Error",
  /*  1 */ "Debug",
  /*  2 */ "NMI Interrupt",
  /*  3 */ "Breakpoint",
  /*  4 */ "Overflow",
  /*  5 */ "BOUND Range Exceeded",
  /*  6 */ "Invalid Opcode",
  /*  7 */ "Device Not Available",
  /*  8 */ "Double Fault",
  /*  9 */ "CoProcessor Segment Overrrun",
  /* 10 */ "Invalid TSS",
  /* 11 */ "Segment Not Present",
  /* 12 */ "Stack Segment Fault",
  /* 13 */ "General Protection",
  /* 14 */ "Page Fault",
  /* 15 */ "Reserved",
  /* 16 */ "Floating-Point Error",
  /* 17 */ "Alignment Check",
  /* 18 */ "Machine Check",
  /* 19 */ "SIMD Floating-Point Exception",
  /* 20 */ "Reserved",
  /* 21 */ "Reserved",
  /* 22 */ "Reserved",
  /* 23 */ "Reserved",
  /* 24 */ "Reserved",
  /* 25 */ "Reserved",
  /* 26 */ "Reserved",
  /* 27 */ "Reserved",
  /* 28 */ "Reserved",
  /* 29 */ "Reserved",
  /* 30 */ "Reserved",
  /* 31 */ "Reserved"
};
#line 1269 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

//----------------------------------------------------------------------------

#line 1832 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


//----------------------------------------------------------------------------


#line 675 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
Cpu::Cpu(Cpu_number cpu)
{
  set_id(cpu);
  if (cpu == Cpu_number::boot_cpu())
    {
      _boot_cpu = this;
      set_present(1);
      set_online(1);
    }

  init();
}

#line 689 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



void
Cpu::init_global_features()
{}

#line 695 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


char const *
Cpu::exception_string(Mword trapno)
{
  if (trapno > 32)
    return "Maskable Interrupt";
  return exception_strings[trapno];
}

#line 724 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


void
Cpu::update_features_info()
{
  cpuid(1, &_version, &_brand, &_ext_features, &_features);
}

#line 731 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::cache_tlb_intel()
{
  Unsigned8 desc[16];
  unsigned i, count = 0;
  Cache_table const *table;

  do
    {
      cpuid(2, (Unsigned32 *)(desc),
               (Unsigned32 *)(desc + 4),
               (Unsigned32 *)(desc + 8),
               (Unsigned32 *)(desc + 12));

      for (i = 1; i < 16; i++)
	{
	  // Null descriptor or register bit31 set (reserved)
	  if (!desc[i] || (desc[i / 4 * 4 + 3] & (1 << 7)))
	    continue;

	  for (table = intel_cache_table; table->desc; table++)
	    {
	      if (table->desc == desc[i])
		{
		  switch (table->level)
		    {
		    case Cache_l1_data:
		      _l1_data_cache_size      = table->size;
		      _l1_data_cache_asso      = table->asso;
		      _l1_data_cache_line_size = table->line_size;
		      break;
		    case Cache_l1_inst:
		      _l1_inst_cache_size      = table->size;
		      _l1_inst_cache_asso      = table->asso;
		      _l1_inst_cache_line_size = table->line_size;
		      break;
		    case Cache_l1_trace:
		      _l1_trace_cache_size = table->size;
		      _l1_trace_cache_asso = table->asso;
		      break;
		    case Cache_l2:
		      _l2_cache_size      = table->size;
		      _l2_cache_asso      = table->asso;
		      _l2_cache_line_size = table->line_size;
		      break;
		    case Cache_l3:
		      _l3_cache_size      = table->size;
		      _l3_cache_asso      = table->asso;
		      _l3_cache_line_size = table->line_size;
		      break;
		    case Tlb_inst_4k:
		      _inst_tlb_4k_entries += table->size;
		      break;
		    case Tlb_data_4k:
		      _data_tlb_4k_entries += table->size;
		      break;
		    case Tlb_inst_4M:
		      _inst_tlb_4m_entries += table->size;
		      break;
		    case Tlb_data_4M:
		      _data_tlb_4m_entries += table->size;
		      break;
		    case Tlb_inst_4k_4M:
		      _inst_tlb_4k_4m_entries += table->size;
		      break;
		    case Tlb_data_4k_4M:
		      _data_tlb_4k_4m_entries += table->size;
		      break;
		    default:
		      break;
		    }
		  break;
		}
	    }
	}
    }
  while (++count < *desc);
}

#line 811 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::cache_tlb_l1()
{
  Unsigned32 eax, ebx, ecx, edx;
  cpuid(0x80000005, &eax, &ebx, &ecx, &edx);

  _l1_data_cache_size      = (ecx >> 24) & 0xFF;
  _l1_data_cache_asso      = (ecx >> 16) & 0xFF;
  _l1_data_cache_line_size =  ecx        & 0xFF;

  _l1_inst_cache_size      = (edx >> 24) & 0xFF;
  _l1_inst_cache_asso      = (edx >> 16) & 0xFF;
  _l1_inst_cache_line_size =  edx        & 0xFF;

  _data_tlb_4k_entries     = (ebx >> 16) & 0xFF;
  _inst_tlb_4k_entries     =  ebx        & 0xFF;
  _data_tlb_4m_entries     = (eax >> 16) & 0xFF;
  _inst_tlb_4m_entries     =  eax        & 0xFF;
}

#line 832 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::cache_tlb_l2_l3()
{
  Unsigned32 eax, ebx, ecx, edx;
  cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

  if (vendor() == Vendor_via)
    {
      _l2_cache_size          = (ecx >> 24) & 0xFF;
      _l2_cache_asso          = (ecx >> 16) & 0xFF;
    }
  else
    {
      _l2_data_tlb_4m_entries = (eax >> 16) & 0xFFF;
      _l2_inst_tlb_4m_entries =  eax        & 0xFFF;
      _l2_data_tlb_4k_entries = (ebx >> 16) & 0xFFF;
      _l2_inst_tlb_4k_entries =  ebx        & 0xFFF;
      _l2_cache_size          = (ecx >> 16) & 0xFFFF;
      _l2_cache_asso          = (ecx >> 12) & 0xF;
    }

  _l2_cache_line_size = ecx & 0xFF;

  _l3_cache_size      = (edx >> 18) << 9;
  _l3_cache_asso      = (edx >> 12) & 0xF;
  _l3_cache_line_size = edx & 0xFF;
}

#line 861 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::addr_size_info()
{
  Unsigned32 eax, ebx, ecx, edx;
  cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

  _phys_bits = eax & 0xff;
  _virt_bits = (eax & 0xff00) >> 8;
}

#line 872 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


unsigned
Cpu::amd_cpuid_mnc()
{
  Unsigned32 eax, ebx, ecx, edx;
  cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

  unsigned apicidcoreidsize = (ecx >> 12) & 0xf;
  if (apicidcoreidsize == 0)
    return (ecx & 0xf) + 1; // NC
  return 1 << apicidcoreidsize;
}

#line 885 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::set_model_str()
{
  Vendor_table const *table;

  if (_model_str[0])
    return;

  for (table = vendor_table[vendor()]; table && table->vendor_mask; table++)
    if ((_version & table->vendor_mask) == table->vendor_code &&
        (table->l2_cache == 0xFFFF || _l2_cache_size >= table->l2_cache))
      {
	snprintf(_model_str, sizeof (_model_str), "%s",
		 table->vendor_string);
	return;
      }

  snprintf(_model_str, sizeof (_model_str), "Unknown CPU");
}

#line 915 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


unsigned long
Cpu::get_features()
{
  Unsigned32 eflags = get_flags();
  // Check for Alignment Check Support
  set_flags(eflags ^ EFLAGS_AC);
  if (((get_flags() ^ eflags) & EFLAGS_AC) == 0)
    return 0;

  // Check for CPUID Support
  set_flags(eflags ^ EFLAGS_ID);
  if (!((get_flags() ^ eflags) & EFLAGS_ID))
    return 0;

  Unsigned32 max;
  char vendor_id[12];

  cpuid(0, &max, (Unsigned32 *)(vendor_id),
                 (Unsigned32 *)(vendor_id + 8),
                 (Unsigned32 *)(vendor_id + 4));

  if (!max)
    return 0;

  Unsigned32 dummy, dummy1, dummy2, features;
  cpuid(1, &dummy, &dummy1, &dummy2, &features);

  return features;
}

#line 946 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


/** Identify the CPU features.
    Attention: This function may be called more than once. The reason is
    that enabling a Local APIC that was previously disabled by the BIOS
    may change the processor features. Therefore, this function has to
    be called again after the Local APIC was enabled.
 */
FIASCO_INIT_CPU
void
Cpu::identify()
{
  Unsigned32 eflags = get_flags();

  _phys_bits = 32;
  _virt_bits = 32;

  // Reset members in case we get called more than once
  _inst_tlb_4k_entries    =
  _data_tlb_4k_entries    =
  _inst_tlb_4m_entries    =
  _data_tlb_4m_entries    =
  _inst_tlb_4k_4m_entries =
  _data_tlb_4k_4m_entries = 0;

  // Check for Alignment Check Support
  set_flags(eflags ^ EFLAGS_AC);
  // FIXME: must not panic at cpu hotplug
  if (((get_flags() ^ eflags) & EFLAGS_AC) == 0)
    panic("CPU too old");

  // Check for CPUID Support
  set_flags(eflags ^ EFLAGS_ID);
  if ((get_flags() ^ eflags) & EFLAGS_ID) {

    Unsigned32 max, i;
    char vendor_id[12];

    cpuid(0, &max, (Unsigned32 *)(vendor_id),
                   (Unsigned32 *)(vendor_id + 8),
                   (Unsigned32 *)(vendor_id + 4));

    for (i = sizeof (vendor_ident) / sizeof (*vendor_ident) - 1; i; i--)
      if (!memcmp(vendor_id, vendor_ident[i], 12))
        break;

    _vendor = (Cpu::Vendor)i;

    init_indirect_branch_mitigation();

    switch (max)
      {
      default:
	// All cases fall through!
      case 10:
        cpuid(10, &_arch_perfmon_info_eax,
                  &_arch_perfmon_info_ebx,
                  &_arch_perfmon_info_ecx, &i);
        // FALLTHRU
      case 2:
        if (_vendor == Vendor_intel)
          cache_tlb_intel();
        // FALLTHRU
      case 1:
        update_features_info();
      }

    if (max >= 5 && has_monitor_mwait())
      cpuid(5, &_monitor_mwait_eax, &_monitor_mwait_ebx,
               &_monitor_mwait_ecx, &_monitor_mwait_edx);

    _thermal_and_pm_eax = 0;
    if (max >= 6 && _vendor == Vendor_intel)
      {
        Unsigned32 dummy;
        cpuid(6, &_thermal_and_pm_eax, &dummy, &dummy, &dummy);
      }

    try_enable_hw_performance_states(false);

    if (max >= 7 && _vendor == Vendor_intel)
      {
        Unsigned32 dummy1, dummy2, dummy3;
        cpuid(0x7, 0, &dummy1, &_ext_07_ebx, &dummy2, &dummy3);
      }

    if (_vendor == Vendor_intel)
      {
	switch (family())
	  {
	  case 5:
	    // Avoid Pentium Erratum 74
	    if ((_features & FEAT_MMX) &&
		(model() != 4 ||
		 (stepping() != 4 && (stepping() != 3 || type() != 1))))
	      _local_features |= Lf_rdpmc;
	    break;
	  case 6:
	    // Avoid Pentium Pro Erratum 26
	    if (model() >= 3 || stepping() > 9)
	      _local_features |= Lf_rdpmc;
	    break;
	  case 15:
	    _local_features |= Lf_rdpmc;
	    _local_features |= Lf_rdpmc32;
	    break;
	  }
      }
    else if (_vendor == Vendor_amd)
      {
	switch (family())
	  {
	  case 6:
	  case 15:
	    _local_features |= Lf_rdpmc;
	    break;
	  }
      }

    // Get maximum number for extended functions
    cpuid(0x80000000, &max, &i, &i, &i);

    if (max > 0x80000000)
      {
	switch (max)
	  {
	  default:
	    // FALLTHRU
	  case 0x80000008:
	    if (_vendor == Vendor_amd || _vendor == Vendor_intel)
	      addr_size_info();
	    // FALLTHRU
	  case 0x80000007:
	  case 0x80000006:
	    if (_vendor == Vendor_amd || _vendor == Vendor_via)
	      cache_tlb_l2_l3();
	    // FALLTHRU
	  case 0x80000005:
	    if (_vendor == Vendor_amd || _vendor == Vendor_via)
	      cache_tlb_l1();
	    // FALLTHRU
	  case 0x80000004:
	    {
	      Unsigned32 *s = (Unsigned32 *)_model_str;
	      for (unsigned i = 0; i < 3; ++i)
	        cpuid(0x80000002 + i, &s[0 + 4*i], &s[1 + 4*i],
                                      &s[2 + 4*i], &s[3 + 4*i]);
	      _model_str[48] = 0;
	    }
	    // FALLTHRU
	  case 0x80000003:
	  case 0x80000002:
	  case 0x80000001:
	    if (_vendor == Vendor_intel || _vendor == Vendor_amd)
              cpuid(0x80000001, &i, &i, &_ext_8000_0001_ecx,
                                &_ext_8000_0001_edx);
	    break;
	  }
      }

    // see Intel Spec on SYSENTER:
    // Some Pentium Pro pretend to have it, but actually lack it
    if ((_version & 0xFFF) < 0x633)
      _features &= ~FEAT_SEP;

  } else
    _version = 0x400;

  set_model_str();

  set_flags(eflags);
}

#line 1128 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


bool
Cpu::if_show_infos() const
{
  return    id() == Cpu_number::boot_cpu()
         || !boot_cpu()
         || family()    != boot_cpu()->family()
         || model()     != boot_cpu()->model()
         || stepping()  != boot_cpu()->stepping()
         || brand()     != boot_cpu()->brand();
}

#line 1140 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


void
Cpu::show_cache_tlb_info(const char *indent) const
{
  if (!if_show_infos())
    return;

  char s[16];

  *s = '\0';
  if (_l2_inst_tlb_4k_entries)
    snprintf(s, sizeof(s), "/%d", _l2_inst_tlb_4k_entries);
  if (_inst_tlb_4k_entries)
    printf("%s%4d%s Entry I TLB (4K pages)", indent, _inst_tlb_4k_entries, s);
  *s = '\0';
  if (_l2_inst_tlb_4m_entries)
    snprintf(s, sizeof(s), "/%d", _l2_inst_tlb_4k_entries);
  if (_inst_tlb_4m_entries)
    printf("   %4d%s Entry I TLB (4M pages)", _inst_tlb_4m_entries, s);
  if (_inst_tlb_4k_4m_entries)
    printf("%s%4d Entry I TLB (4K or 4M pages)",
           indent, _inst_tlb_4k_4m_entries);
  if (_inst_tlb_4k_entries || _inst_tlb_4m_entries || _inst_tlb_4k_4m_entries)
    putchar('\n');
  *s = '\0';
  if (_l2_data_tlb_4k_entries)
    snprintf(s, sizeof(s), "/%d", _l2_data_tlb_4k_entries);
  if (_data_tlb_4k_entries)
    printf("%s%4d%s Entry D TLB (4K pages)", indent, _data_tlb_4k_entries, s);
  *s = '\0';
  if (_l2_data_tlb_4m_entries)
    snprintf(s, sizeof(s), "/%d", _l2_data_tlb_4m_entries);
  if (_data_tlb_4m_entries)
    printf("   %4d%s Entry D TLB (4M pages)", _data_tlb_4m_entries, s);
  if (_data_tlb_4k_4m_entries)
    printf("%s%4d Entry D TLB (4k or 4M pages)",
           indent, _data_tlb_4k_4m_entries);
  if (_data_tlb_4k_entries || _data_tlb_4m_entries || _data_tlb_4k_4m_entries)
    putchar('\n');

  if (_l1_trace_cache_size)
    printf("%s%3dK %c-ops T Cache (%d-way associative)\n",
           indent, _l1_trace_cache_size, Config::char_micro,
           _l1_trace_cache_asso);

  else if (_l1_inst_cache_size)
    printf("%s%4d KB L1 I Cache (%d-way associative, %d bytes per line)\n",
           indent, _l1_inst_cache_size, _l1_inst_cache_asso,
           _l1_inst_cache_line_size);

  if (_l1_data_cache_size)
    printf("%s%4d KB L1 D Cache (%d-way associative, %d bytes per line)\n"
           "%s%4d KB L2 U Cache (%d-way associative, %d bytes per line)\n",
           indent, _l1_data_cache_size, _l1_data_cache_asso,
           _l1_data_cache_line_size,
           indent, _l2_cache_size, _l2_cache_asso, _l2_cache_line_size);

  if (_l3_cache_size)
    printf("%s%4u KB L3 U Cache (%d-way associative, %d bytes per line)\n",
           indent, _l3_cache_size, _l3_cache_asso, _l3_cache_line_size);
}

#line 1202 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


void
Cpu::disable(Cpu_number cpu, char const *reason)
{
  printf("CPU%u: is disabled: %s\n", cxx::int_value<Cpu_number>(cpu), reason);
}

#line 1289 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_AND_PM
void
Cpu::pm_suspend()
{
  Gdt_entry tss_entry;
  tss_entry = (*gdt)[Gdt::gdt_tss / 8];
  tss_entry.access &= 0xfd;
  (*gdt)[Gdt::gdt_tss / 8] = tss_entry;
  _suspend_tsc = rdtsc();
}

#line 1300 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_AND_PM
void
Cpu::pm_resume()
{
  if (id() != Cpu_number::boot_cpu())
    {
      // the boot CPU restores some state in asm already
      set_gdt();
      set_ldt(0);
      set_ds(Gdt::data_segment());
      set_es(Gdt::data_segment());
      set_ss(Gdt::gdt_data_kernel | Gdt::Selector_kernel);
      set_fs(Gdt::gdt_data_user   | Gdt::Selector_user);
      set_gs(Gdt::gdt_data_user   | Gdt::Selector_user);
      set_cs();

      set_tss();
    }
  init_indirect_branch_mitigation();

  init_sysenter();
  wrmsr(_suspend_tsc, MSR_TSC);

  try_enable_hw_performance_states(true);
}

#line 1447 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


FIASCO_INIT_CPU
void
Cpu::init_lbr_type()
{
  _lbr = Lbr_unsupported;

  if (can_wrmsr())
    {
      // Intel
      if (vendor() == Vendor_intel)
	{
	  if (family() == 15)
	    _lbr = model() < 3 ? Lbr_pentium_4 : Lbr_pentium_4_ext; // P4
	  else if (family() >= 6)
	    _lbr = Lbr_pentium_6; // PPro, PIII
	}
      else if (vendor() == Vendor_amd)
	{
	  if ((family() == 6) || (family() == 15))
	    _lbr = Lbr_pentium_6; // K7/K8
	}
    }
}

#line 1472 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


FIASCO_INIT_CPU
void
Cpu::init_bts_type()
{
  _bts = Bts_unsupported;

  if (can_wrmsr() && vendor() == Vendor_intel)
    {
      if (family() == 15 && (rdmsr(0x1A0) & (1<<11)) == 0)
	_bts = Bts_pentium_4;
      if (family() == 6  && (model() == 9 || (model() >= 13 &&
	      model() <= 15)))
	_bts = Bts_pentium_m;
      if (!(features() & FEAT_DS))
	_bts = Bts_unsupported;
    }
}

#line 1538 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"



void
Cpu::bts_enable(bool on)
{
  if (bts_type() != Bts_unsupported)
    {
      if (on)
	{
	  switch (bts_type())
	    {
	    case Bts_pentium_4: bts_active = true; debugctl_set |= 0x0c; break;
	    case Bts_pentium_m: bts_active = true; debugctl_set |= 0xc0; break;
	    default:;
	    }
	  debugctl_busy = lbr_active || bts_active;
	}
      else
	{
	  bts_active = false;
	  switch (bts_type())
	    {
	    case Bts_pentium_4: debugctl_set &= ~0x0c; break;
	    case Bts_pentium_m: debugctl_set &= ~0xc0; break;
	    default:;
	    }
	  debugctl_busy = lbr_active || bts_active;
	  wrmsr(debugctl_reset, MSR_DEBUGCTLA);
	}
    }
}

#line 1586 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

/*
 * AMD OS-Visible Workaround Information
 * print a warning if a CPU is affected by any known erratum
 */

void
Cpu::print_errata()
{
  if (vendor() == Vendor_amd && has_amd_osvw() && can_wrmsr())
    {
      Unsigned16 osvw_id_length, i;
      bool affected = false;
      osvw_id_length = rdmsr(0xc0010140) & 0xff;

      for (i = 1; ((i - 1) * 64) < osvw_id_length; i++)
        {
          Unsigned64 osvw_msr = rdmsr(0xc0010140 + i);
          if (osvw_msr != 0)
            {
              printf("\033[31mOSVW_MSR%d = 0x%016llx\033[m\n",
                     i, rdmsr(0xc0010140 + i));
              affected = true;
            }
        }
      if (affected)
        printf("\033[31m#Errata known %d, affected by at least one\033[m\n",
               osvw_id_length);
    }
}

#line 1616 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

/**
 * Enable hardware controlled performance states (HWP) if available.
 *
 * HWP enables the processor to autonomously select performance states. The OS
 * can hint the CPU at the desired optimizations. For example, a system running
 * on battery may hint the CPU to optimize for low power consumption. We just
 * enable HWP and configure it to select the performance target autonomously.
 *
 * See Intel Manual Volume 3 Chapter 14.4 for details.
 */
FIASCO_INIT_CPU
void
Cpu::try_enable_hw_performance_states(bool resume)
{
  enum
  {
    HWP_SUPPORT = 1 << 7,
    HIGHEST_PERFORMANCE_SHIFT = 0,
    LOWEST_PERFORMANCE_SHIFT = 24
  };

  if (!(_thermal_and_pm_eax & HWP_SUPPORT))
    return;

  // enable
  wrmsr(0x1ULL, MSR_HWP_PM_ENABLE);

  // let the hardware decide on everything (autonomous operation mode)
  Unsigned64 hwp_caps = rdmsr(MSR_HWP_CAPABILITIES);
  // Package_Control (bit 42) = 0
  // Activity_Window (bits 41:32) = 0 (auto)
  // Energy_Performance_Preference (bits 31:24) = 0x80 (default)
  // Desired_Performance (bits 23:16) = 0 (default)
  // Maximum_Performance (bits 15:8) = HIGHEST_PERFORMANCE(hwp_cap)
  // Minimum_Performance (bits 7:0) = LOWEST_PERFORMANCE(hwp_cap)
  Unsigned64 request =
    0x80ULL << 24 |
    (((hwp_caps >> HIGHEST_PERFORMANCE_SHIFT) & 0xff) << 8) |
    ((hwp_caps >> LOWEST_PERFORMANCE_SHIFT) & 0xff);
  wrmsr(request, MSR_HWP_REQUEST);

  if (!resume && id() == Cpu_number::boot_cpu())
    printf("HWP: enabled\n");
}

#line 1661 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

FIASCO_INIT_CPU
void
Cpu::init()
{
  identify();

  init_lbr_type();
  init_bts_type();

  calibrate_tsc();

  Unsigned32 cr4 = get_cr4();

  if (features() & FEAT_FXSR)
    cr4 |= CR4_OSFXSR;

  if (features() & FEAT_SSE)
    cr4 |= CR4_OSXMMEXCPT;

  // enable SMEP if available
  if (has_smep())
    cr4 |= CR4_SMEP;

  set_cr4 (cr4);

  if ((features() & FEAT_TSC) && can_wrmsr())
    {
      if (_ext_07_ebx & FEATX_IA32_TSC_ADJUST)
        wrmsr(0, 0, MSR_IA32_TSC_ADJUST);
      else
        // at least reset time stamp counter (better for debugging)
        wrmsr(0, 0, MSR_TSC);
    }

  if ((features() & FEAT_PAT) && can_wrmsr())
    wrmsr(0x00010406, 0x00070406, MSR_PAT);

  print_errata();
}

#line 1701 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"


void
Cpu::print_infos() const
{
  if (if_show_infos())
    printf("CPU[%u]: %s (%X:%X:%X:%X)[%08x] Model: %s at %lluMHz\n\n",
           cxx::int_value<Cpu_number>(id()),
           vendor_str(), family(), model(), stepping(), brand(),
           _version, model_str(),
           div32(frequency(), 1000000));

  show_cache_tlb_info("");
}

#line 1715 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/kern/ia32/cpu-ia32.cpp"

// Return 2^32 / (tsc clocks per usec)
FIASCO_INIT_CPU
void
Cpu::calibrate_tsc()
{
  const unsigned calibrate_time = 50000 /*us*/ + 1;

  // sanity check
  if (! (features() & FEAT_TSC))
    goto bad_ctc;

  // only do once
  if (scaler_tsc_to_ns)
    return;

  Unsigned64 tsc_start, tsc_end;
  Unsigned32 count, tsc_to_ns_div, dummy;

    {
      static Spin_lock<> _l;
      auto guard = lock_guard(_l);

      Pit::setup_channel2_to_20hz();

      tsc_start = rdtsc ();
      count = 0;
      do
	{
	  count++;
	}
      while ((Io::in8 (0x61) & 0x20) == 0);
      tsc_end = rdtsc ();
    }

  // Error: ECTCNEVERSET
  if (count <= 1)
    goto bad_ctc;

  tsc_end -= tsc_start;

  // prevent overflow in division (CPU too fast)
  if (tsc_end & 0xffffffff00000000LL)
    goto bad_ctc;

  // prevent overflow in division (CPU too slow)
  if ((tsc_end & 0xffffffffL) < calibrate_time)
    goto bad_ctc;

  // tsc_to_ns_div = calibrate_time * 2^32 / tsc
  asm ("divl %2"
       :"=a" (tsc_to_ns_div), "=d" (dummy)
       :"r" ((Unsigned32)tsc_end), "a" (0), "d" (calibrate_time));

  // scaler_tsc_to_ns = (tsc_to_ns_div * 1000) / 32
  // not using muldiv(tsc_to_ns_div, 1000, 1 << 5), as div result > (1 << 32)
  // will get trap0 if system frequency is too low
  scaler_tsc_to_ns  = tsc_to_ns_div * 31;
  scaler_tsc_to_ns += tsc_to_ns_div / 4;
  scaler_tsc_to_us  = tsc_to_ns_div;
  scaler_ns_to_tsc  = muldiv(1 << 31, ((Unsigned32)tsc_end),
                             calibrate_time * 1000 >> 1 * 1 << 5);

  if (scaler_tsc_to_ns)
    _frequency = ns_to_tsc(1000000000UL);

  return;

bad_ctc:
  if (Config::Kip_timer_uses_rdtsc)
    panic("Can't calibrate tsc");
}
