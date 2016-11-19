
#ifndef __SQLITE3__
   #include <sqlite3.h> 
#endif
#include <stdio.h>
#include <stdlib.h>
#include "novas.h"

#define MAXSTARS (175)
#define MINMAG  (3)





int main(int argc, char* argv[])
{

   cat_entry stars[175]; 
   sqlite3 *db;
   const char *dbpath="/home/pi/STaRTrack/HYG-Database-master/startchart.sqlite3";
   char *zErrMsg = 0;
   int rc;
   sqlite3_stmt *stmt;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open(dbpath, &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sqlite3_prepare_v2(db,"SELECT *  FROM stars WHERE mag < ? LIMIT ?;",-1, &stmt, NULL);
   sqlite3_bind_int(stmt, 1, MINMAG);
   sqlite3_bind_int(stmt,2,MAXSTARS);
   int i = 1;
   while ( (rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        /* access by column index */
        printf("%d: %s is %d years old\n", i,sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 1));
        i=i+1;
   }

   sqlite3_finalize(stmt);

}








