/* ========================================================================
 * Copyright 1988-2006 University of Washington
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * 
 * ========================================================================
 */

/*
 * Program:	KOI8-U conversion table
 *
 * Author:	Mark Crispin
 *		Networks and Distributed Computing
 *		Computing & Communications
 *		University of Washington
 *		Administration Building, AG-44
 *		Seattle, WA  98195
 *		Internet: MRC@CAC.Washington.EDU
 *
 * Date:	25 August 1997
 * Last Edited:	30 August 2006
 */

/* KOI8-U is a de-facto standard of Ukraine */

static const unsigned short koi8utab[128] = {
  0x2500,0x2502,0x250c,0x2510,0x2514,0x2518,0x251c,0x2524,
  0x252c,0x2534,0x253c,0x2580,0x2584,0x2588,0x258c,0x2590,
  0x2591,0x2592,0x2593,0x2320,0x25a0,0x2219,0x221a,0x2248,
  0x2264,0x2265,0x00a0,0x2321,0x00b0,0x00b2,0x00b7,0x00f7,
  0x2550,0x2551,0x2552,0x0451,0x0454,0x2554,0x0456,0x0457,
  0x2557,0x2558,0x2559,0x255a,0x255b,0x0491,0x255d,0x255e,
  0x255f,0x2560,0x2561,0x0401,0x0403,0x2563,0x0406,0x0407,
  0x2566,0x2567,0x2568,0x2569,0x256a,0x0490,0x256c,0x00a9,
  0x044e,0x0430,0x0431,0x0446,0x0434,0x0435,0x0444,0x0433,
  0x0445,0x0438,0x0439,0x043a,0x043b,0x043c,0x043d,0x043e,
  0x043f,0x044f,0x0440,0x0441,0x0442,0x0443,0x0436,0x0432,
  0x044c,0x044b,0x0437,0x0448,0x044d,0x0449,0x0447,0x044a,
  0x042e,0x0410,0x0411,0x0426,0x0414,0x0415,0x0424,0x0413,
  0x0425,0x0418,0x0419,0x041a,0x041b,0x041c,0x041d,0x041e,
  0x041f,0x042f,0x0420,0x0421,0x0422,0x0423,0x0416,0x0412,
  0x042c,0x042b,0x0417,0x0428,0x042d,0x0429,0x0427,0x042a
};
