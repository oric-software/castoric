

#define        via_portb               $0300 
#define		   via_ddrb				   $0302	
#define		   via_ddra				   $0303
#define        via_t1cl                $0304 
#define        via_t1ch                $0305 
#define        via_t1ll                $0306 
#define        via_t1lh                $0307 
#define        via_t2ll                $0308 
#define        via_t2ch                $0309 
#define        via_sr                  $030A 
#define        via_acr                 $030b 

/*
    PERIPHERAL CONTROL REGISTER

    |----+----+----+----+----+----+----+----|
    |  7 | 6  |  5 |  4 | 3  | 2  | 1  | 0  |
    |----+----+----+----+----+----+----+----|
    |  CB2 Control | CB1| CA2 Control  | CA1|
    |----+----+----+----+----+----+----+----|

CA/B1 CTRL : 0 => sensitive to negative transition
             1 => sensitive to positive transition
CA/B2 CTRL :

*/

#define        via_pcr                 $030c 

/*
    INTERRUPT FLAG REGISTER
The IFR is a read/bit clear register 

Bit 7    indicates the status of the IRQ
Bit 6-0  are latches 
    0 : Set by Active transition of the signal on the CA2 pin
    1 : Set by Active transition of the signal on the CA1 pin
            both cleared by reading the port A ouput register (ORA) adr 0001
    2 : Set by Completion of 8 shifts
            cleared by reading or writing the shift register
    3 : Set by Active transition of the signal on the CB2 pin
    4 : Set by Active transition of the signal on the CB1 pin
            both cleared by reading the port B ouput register
    5 : Set by Timer 2 timeout
            cleared by reading T2 lsb counter or writing T2 msb counter
    6 : Set by Timer 1 timeout
            cleared by reading T1 lsb counter or writing T1 msb counter
*/

#define        via_ifr                 $030D 

/* 
    INTERUPT ENABLE REGISTER


*/
#define        via_ier                 $030E 
#define        via_porta               $030f 
