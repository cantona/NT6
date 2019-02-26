// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "烽火台");
        set("long", @LONG        
這是高麗位於海邊的一個烽火台。有幾個官兵正在這裏觀海上的情
況。放眼望去，一片碧波，沒有邊際。看來現在還是風平浪靜。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "eastdown" : __DIR__"xiaolu2",
        ]));
        set("objects",([
          __DIR__"npc/bing":2,
          ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","fenghuotai");
  return ::valid_leave(ob,dir);
}
