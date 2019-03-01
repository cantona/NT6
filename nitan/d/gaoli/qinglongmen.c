// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "飛鳳門");
        set("long", @LONG
這裡是高麗的飛鳳門。東面就到了城中，遠望人山人海，往來行人
車流不絕。西面一條大路通向中原。城門下有一些執勤的兵士。兵將警
惕的盯著往來人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"qinglong-2",
                "west" : __DIR__"edao1",
                "southwest":__DIR__"dadi",
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
    ob->add_temp_array("xunluo_dir","qinglong");
  return ::valid_leave(ob,dir);
}
