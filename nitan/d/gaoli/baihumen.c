// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "朝陽門");
        set("long", @LONG
這裏是高麗的朝陽門。西面就到了城中，遠望人山人海，往來行人
車流不絕。東面一條大路通向新羅和百濟。城門下有一些執勤的兵士。
兵將警惕的盯着往來人士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"baihu-2",
                "east" : __DIR__"dadao1",
                "northeast":__DIR__"shulin1",
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
    ob->add_temp_array("xunluo_dir","baihu");
  return ::valid_leave(ob,dir);
}
