//Room: miao.c
#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "城隍廟");
        set("long", @LONG
廟有一大半傾塌了，本來就不大，現在就顯得更小了，不過小無
減於它的懾人氣氛。沒有傾塌的是神殿的一角，而且剛好是神像所在
的地方，所以那尊土塑的山神還算是完好的。這也不知是比照哪一位
尊神所塑的像？青面獠牙，眼睛瞪得像兩枚銅鈴，而且還熠熠發光。
旁邊還有一張破舊的桌子，桌上掛了一塊木匾（bian）。
LONG );
        set("exits", ([
                "west"   : "/d/changan/yongtai-dadao4",
        ]));
        set("objects", ([
                "/d/changan/npc/keeper"   : 1,
                __DIR__"obj/table" : 1,
                __DIR__"npc/shensuan" : 1,
        ]));
        set("item_desc", ([
                "bian" : "人有旦夕禍福，天有不測風雲。",
        ]));

        set("no_fight",1);
        set("coor/x", -10750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_knock","knock");
        remove_call_out("stat");
        call_out("stat", 10, this_player());
        remove_call_out("do_sleep");
        call_out("do_sleep",110+random(10));
}
int do_knock(string arg)
{
        object me,ob;
        me = this_player();
        ob = present("shensuan zi",this_object());
        if (ob){
         if(!arg || arg != "table")   return notify_fail("你要敲什麼？\n");
         if( !query_temp("sleeped", ob) )
            return notify_fail("賽神仙已經醒了，不必再敲桌子了。\n");
         delete_temp("sleeped", ob);
         delete("no_get", ob);
         delete("no_get_from", ob);
         ob->enable_player();
         set("long", "他就是遠近聞名的神算子“賽半仙”，很多人都慕名而來找他算命。\n"HIY"他看起來似乎隱藏了一些天大的祕密。\n"NOR, ob);
         message_vision("$N用力敲了敲桌子。\n",me);
         message_vision("賽半仙睜開睡意朦朧的眼睛，伸了個懶腰，不懷好意的看了看$N。\n",me);
          set_temp("knock", 1, me);
         remove_call_out("do_sleep");
         call_out("do_sleep",60);
         return 1;
        }else  return notify_fail("你得等賽神仙回來再説，\n");
}

void do_sleep()
{
      object ob;

      remove_call_out("do_sleep");
      ob=present("shensuan zi",this_object());
      if (ob && living(ob)){
      message_vision("$N打了個哈欠，又睡着了。\n",ob);
      set_temp("sleeped", 1, ob);
      set("no_get", 1, ob);
      set("no_get_from", 1, ob);
      ob->disable_player("<睡夢中>");
      set("long", "神算子正坐在板凳頭趴在桌子上睡覺，唾液一直流到了桌子底下。\n", ob);
      }
      
}
int stat(object me)
{
   object ob;
   
   if (!me || environment(me)!=this_object() ) return 1;   
   
   ob=present("shensuan zi",this_object());
   if( ob && query_temp("sleeped", ob)){
      message_vision("呼嚕.....呼.........嚕...............\n",ob);
   }
   remove_call_out("stat");
   call_out("stat",60,me);
}
void reset()
{
   ::reset();
   call_out("do_sleep",0);
}
