// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "得勝門");
        set("long", @LONG
這裡是高麗的得勝門。北面就到了城中，遠望人山人海，往來行人
車流不絕。南面一條大路通向港口。城門下有一些執勤的兵士。兵將警
惕的盯著往來人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south" : __DIR__"dadao6",
                "north" : __DIR__"zhuque-2",
        ]));
set("objects",([
  __DIR__"npc/guanbing":2,
  __DIR__"npc/wujiang":1,
  ]));
       setup();
        
}
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","zhuque");
  return ::valid_leave(ob,dir);
}
