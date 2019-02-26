// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "船艙");
        set("long", @LONG        
這裏是戰船的船艙。這裏現在沒有什麼人。桌子上放着一杯茶，還
有些温熱，看來這裏的人剛出去不久。旁邊還有一張圖紙，似乎是關於
海戰部署的圖紙。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "out" : __DIR__"jiaban",
                //"enter":__DIR__"chuancang",
        ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","zhanchuan");
  return ::valid_leave(ob,dir);
}
