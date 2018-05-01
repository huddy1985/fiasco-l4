// AUTOMATICALLY GENERATED -- DO NOT EDIT!         -*- c++ -*-

#ifndef uart_h
#define uart_h
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

#include "console.h"
#line 123 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

#include "uart_base.h"
#line 2 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"

#include "io_regblock.h"

//
// INTERFACE definition follows 
//

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

/**
 * Platform independent UART stub.
 */
class Uart : public Console
{
public:
  /**
   * Type UART transfer mode (Bits, Stopbits etc.).
   */
  typedef unsigned TransferMode;

  /**
   * Type for baud rate.
   */
  typedef unsigned BaudRate;

  /* These constants must be defined in the 
     arch part of the uart. To define them there
     has the advantage of most efficient definition
     for the hardware.

  static unsigned const PAR_NONE = xxx;
  static unsigned const PAR_EVEN = xxx;
  static unsigned const PAR_ODD  = xxx;
  static unsigned const DAT_5    = xxx;
  static unsigned const DAT_6    = xxx;
  static unsigned const DAT_7    = xxx;
  static unsigned const DAT_8    = xxx;
  static unsigned const STOP_1   = xxx;
  static unsigned const STOP_2   = xxx;

  static unsigned const MODE_8N1 = PAR_NONE | DAT_8 | STOP_1;
  static unsigned const MODE_7E1 = PAR_EVEN | DAT_7 | STOP_1;

  // these two values are to leave either mode
  // or baud rate unchanged on a call to change_mode
  static unsigned const MODE_NC  = xxx;
  static unsigned const BAUD_NC  = xxx;

  */


public:
  /* Interface definition - implemented in the arch part */
  /// ctor
  Uart();

  /// dtor
  ~Uart();

  /**
   * (abstract) Shutdown the serial port.
   */
  void shutdown();

  /**
   * (abstract) Get the IRQ assigned to the port.
   */
  int irq() const;

  /**
   * (abstract) Acknowledge UART interrupt.
   */
  void irq_ack();

  Address base() const;

  /**
   * (abstract) Enable rcv IRQ in UART.
   */
  void enable_rcv_irq();

  /**
   * (abstract) Disable rcv IRQ in UART.
   */
  void disable_rcv_irq();

  /**
   * (abstract) Change transfer mode or speed.
   * @param m the new mode for the transfer, or MODE_NC for no mode change.
   * @param r the new baud rate, or BAUD_NC, for no speed change.
   */
  bool change_mode(TransferMode m, BaudRate r);

  /**
   * (abstract) Get the current transfer mode.
   */
  TransferMode get_mode();

  /**
   * (abstract) Write str.
   */
  int write( char const *str, size_t len );

  /**
   * (abstract) Read a character.
   */
  int getchar( bool blocking = true );

  /**
   * (abstract) Is there anything to read?
   */
  int char_avail() const;
  
  Mword get_attributes() const;

#line 125 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"
private:

public:
    enum
      {
        PAR_NONE = 0x00,
        PAR_EVEN = 0x18,
        PAR_ODD  = 0x08,
        DAT_5    = 0x00,
        DAT_6    = 0x01,
        DAT_7    = 0x02,
        DAT_8    = 0x03,
        STOP_1   = 0x00,
        STOP_2   = 0x04,

        MODE_8N1 = PAR_NONE | DAT_8 | STOP_1,
        MODE_7E1 = PAR_EVEN | DAT_7 | STOP_1,

        // these two values are to leave either mode
        // or baud rate unchanged on a call to change_mode
        MODE_NC  = 0x1000000,
        BAUD_NC  = 0x1000000,

  };

  static L4::Uart *uart();

#line 4 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"
private:

public:
  int _irq;

public:  
#line 21 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"
  bool
  startup(const L4::Io_register_block *r, int irq,
                Unsigned32 base_baud);
};
#line 153 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


//---------------------------------------------------------------------------


//
// IMPLEMENTATION of inline functions (and needed classes)
//


#line 157 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


inline Uart::~Uart()
{ }

#line 161 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

inline void Uart::shutdown()
{
  del_state(ENABLED);
  uart()->shutdown();
}

#line 167 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"

inline bool Uart::change_mode(TransferMode m, BaudRate baud)
{
  return uart()->change_mode(m, baud);
}

#line 172 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


inline int Uart::write(const char *s, __SIZE_TYPE__ count)
{
  return uart()->write(s, count);
}

#line 178 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"


inline int Uart::getchar(bool blocking)
{
  return uart()->get_char(blocking);
}

#line 184 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart.cpp"



inline int Uart::char_avail() const
{
  return uart()->char_avail();
}

#line 33 "/media/fedora_work/project/real-time/l4re/src/kernel/fiasco/src/drivers/uart-16550.cpp"


inline int Uart::irq() const
{
  return _irq;
}

#endif // uart_h
