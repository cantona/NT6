// /d/gaoli/jiaojunchang
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "較軍場");
        set("long", @LONG
這是一座較軍場，空曠曠的一個人也沒有，只有風吹着落葉，打仗
出兵都從這聚集軍隊，秋天的官兵比試也在這進行，遠處的大台是皇上
的御看台。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast":__DIR__"dadao8",  
                 "southwest":__DIR__"dadao7",   
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","jjc");
  return ::valid_leave(ob,dir);
}
