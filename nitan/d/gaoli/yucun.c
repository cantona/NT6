// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "漁村");
        set("long", @LONG
這是高麗的一個漁村，這裏的人都靠打魚為生，海岸邊停滿了漁船。
漁夫們正挑着大擔大擔的魚走着，籮裏的魚還在鮮蹦活跳。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "northeast" : __DIR__"jiangkou",
                "east" : __DIR__"haigang",
                "southeast" : __DIR__"yuchuan",
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","yucun");
  return ::valid_leave(ob,dir);
}
