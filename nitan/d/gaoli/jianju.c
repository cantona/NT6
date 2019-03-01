// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "北城監獄");
        set("long", @LONG
這裡就是高麗的北城監獄了。面前是一道高牆，就是武林高手也難
以躍過。門口站著幾個官兵，正上上下下地打量著你。裡面不時傳來犯
人慘叫的聲音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "east" : __DIR__"shanlu16",
                       //"west":__DIR__"jianju",
        ]));
        set("objects",([
         __DIR__"npc/bing":4,
         ]));
       setup();
        
}
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","jianyu");
  return ::valid_leave(ob,dir);
}
