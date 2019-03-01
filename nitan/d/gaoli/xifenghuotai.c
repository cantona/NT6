// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "烽火台");
        set("long", @LONG        
這是高麗位于西邊山峰上的一個烽火台。有幾個官兵正在這裡觀察
情況。從這裡可以看到東邊高麗城的全貌，非常壯觀。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "eastdown" : __DIR__"shanlu5",
                
        ]));
     set("objects",([
       __DIR__"npc/bing":2,
       ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","xfenghuotai");
  return ::valid_leave(ob,dir);
}
