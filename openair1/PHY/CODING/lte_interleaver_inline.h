/*******************************************************************************

  Eurecom OpenAirInterface
  Copyright(c) 1999 - 2014 Eurecom

  This program is free software; you can redistribute it and/or modify it under 
  the terms of the GNU General Public License as published by the Free Software 
  Foundation; either version 2 of the License, or (at your option) any later version

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information
  Openair Admin: openair_admin@eurecom.fr
  Openair Tech : openair_tech@eurecom.fr
  Forums       : http://forums.eurecom.fsr/openairinterface
  Address      : Eurecom, 2229, route des cr�tes, 06560 Valbonne Sophia Antipolis, France

*******************************************************************************/

extern unsigned int threegpplte_interleaver_output;
extern unsigned int threegpplte_interleaver_tmp;

extern inline void threegpplte_interleaver_reset(void) {
  threegpplte_interleaver_output = 0;
  threegpplte_interleaver_tmp    = 0;
}

extern inline unsigned short threegpplte_interleaver(unsigned short f1,
					      unsigned short f2,
					      unsigned short K) {

  threegpplte_interleaver_tmp = (threegpplte_interleaver_tmp+(f2<<1));

  threegpplte_interleaver_output = (threegpplte_interleaver_output + threegpplte_interleaver_tmp + f1 - f2)%K;

#ifdef DEBUG_TURBO_ENCODER
  printf("Interleaver output %d\n",threegpplte_interleaver_output);
#endif
  return(threegpplte_interleaver_output);
}


extern inline short threegpp_interleaver_parameters(unsigned short bytes_per_codeword) {
  if (bytes_per_codeword<=64)
    return (bytes_per_codeword-5);
  else if (bytes_per_codeword <=128)
    return (59 + ((bytes_per_codeword-64)>>1));
  else if (bytes_per_codeword <= 256)
    return (91 + ((bytes_per_codeword-128)>>2));
  else if (bytes_per_codeword <= 768)
    return (123 + ((bytes_per_codeword-256)>>3));
  else {
#ifdef DEBUG_TURBO_ENCODER
    printf("Illegal codeword size !!!\n");
#endif 
    return(-1);
  }
}
