#include "test.c"

#define timer_t struct timeval
timer_t get_timer(){
  struct rusage r;
  /*timer_t tm;*/
  /*gettimeofday(&tm, NULL);*/
  getrusage(RUSAGE_SELF, &r);

  return r.ru_stime;
}

double diff_timer(timer_t start, timer_t end){
  /*long int seconds = end.tv_sec - start.tv_sec;*/
  long int micros = end.tv_usec - start.tv_usec;
  return (double) micros;
};

MU_TEST(mem_test) {
  char *buf = malloc(sizeof(char) * 100);
  clock_t start, end;

  strcpy(buf, "hello world");
  printf("buf: %s\n", buf);

  strcpy(buf, "hello world");
  start = clock();
  memmove(buf, buf + 6, 5);
  end = clock();
  printf("buf: %s, time: %lu\n", buf, end - start);

  strcpy(buf, "hello world this is a test");
  start = clock();
  memcpy(buf, buf + 8, 5);
  end = clock();
  printf("memcpy buf: %s, time: %lu\n", buf, end - start);

  strcpy(buf, "hello world this is a test");
  start = clock();
  memmove(buf, buf + 8, 5);
  end = clock();
  printf("memmove buf: %s, time: %lu\n", buf, end - start);

  strcpy(buf, "hello world");
  /*dstart = get_miliseconds();*/
  start = clock();
  memmove(buf + 6, buf, 6);
  end = clock();
  /*dend = get_miliseconds();*/
  /*printf(" lul buf: %s, time: %f\n", buf, dend - dstart);*/

  strcpy(buf, "hello world");
  memset(buf, 0x33 , 4);
  printf("buf: %X %X %X %X \n", buf[0], buf[1], buf[2], buf[3]);

  strcpy(buf, "hello world");
  memmove(buf, buf+1 , 4);
  printf("buf: %s\n", buf);

  strcpy(buf, "hello world");
  memmove(buf+1, buf , 4);
  printf("buf: %s\n", buf);

  /*start = clock();*/
  /*dstart = get_miliseconds();*/
  /*buf[0] = 'a';*/
  /*dend = get_miliseconds();*/
  /*[>end = clock();<]*/
  /*printf("index write wat: %f\n", dend - dstart);*/
  /*[>printf("index write: %lu", end - start);<]*/

  /*start = clock();*/
  /*memset(buf, 'a', 111);*/
  /*end = clock();*/
  /*printf("index write: %f", difftime(start, end));*/
  timer_t tstart, tend;

  double memmove_totoal = 0.0;
  double memcpy_totoal = 0.0;
  double move_result, cpy_result;
  for (int x = 0; x < 24; x++){
    strcpy(buf, "hello world");
    tstart = get_timer();
    for(int i=0; i<1000000; i++){
      memcpy(buf+10, buf , 5);
    }
    tend = get_timer();
    cpy_result = diff_timer(tstart, tend);
    memcpy_totoal += cpy_result;
    printf("memcpy took %f\n", cpy_result);

    strcpy(buf, "hello world");
    tstart = get_timer();
    for(int i=0; i<1000000; i++){
      memmove(buf+10, buf , 5);
    }
    tend = get_timer();
    move_result = diff_timer(tstart, tend);
    memmove_totoal += move_result;
    printf("memmove took %f\n", move_result);

  };

  printf("memmove_totoal: %f\n", memmove_totoal);
  printf("memcpy_totoal: %f\n", memcpy_totoal);
}
