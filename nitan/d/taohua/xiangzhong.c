// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "香冢");
        set("long", @LONG
一轉出桃林，忽然出現了一片白色花叢，重重疊疊，宛似一座白花堆
成的小湖。白花之中有一塊東西高高隆起，定睛一看，原來是一座石墳，
墳前墓碑(mubei)上刻着“桃花島女主馮氏埋香之冢”十一個大字。墓前
四時鮮花常開，每本都是黃藥師精選的天下名種，奇花異卉，各自分香吐豔。
LONG );
        set("item_desc", ([
                "mubei" : "墓碑背面刻着兩行歪歪斜斜的小字：且夫天地為爐兮，造化為工！陰陽為炭兮，\n"
                          "萬物為銅！\n"
                          "墓碑左面，右面，正面似乎特別光滑。\n",
        ]));
        
/*
        set("exits", ([
                "east"  : __DIR__"taolin",
                "north" : __DIR__"road1",
        ]));
*/
              
        set("outdoors", "taohua");

        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_push", "push");
}

int do_push(string arg)
{
          object me = this_player();

          if (!arg) return 0;

        if ( (int)me->query_str() < 28 ) 
        {
                return notify_fail("你沒那麼大力氣搬動墓碑。\n");
        }  
          
        if (arg == "left") 
        {
                    addn_temp("left",1);
                    write("墓碑搖晃了一陣，再不見動靜...\n");
          }

          if ((arg == "right") && ((int)query_temp("left")==3)) {
                    addn_temp("right", 1);
                    write("墓碑搖晃了一陣，再不見動靜...\n");
          }

          if ((arg == "front") && ((int)query_temp("right")==3) && ((int)query_temp("left")==3))
          {
                    write("墓碑搖晃了一陣，緩緩向後倒去，露出一個入口。\n");
                    set("exits/enter", __DIR__"didao");
                    remove_call_out("close_door");
                    call_out("close_door",15,me);
          }

          return 1;
}

void close_door()
{

        if (((int)query_temp("left")!=3) || ((int)query_temp("right")!=3)) 
                return;

          delete("exits/enter");
          delete_temp("left");
          delete_temp("right");
}