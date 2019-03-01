// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "船艙");
        set("long", @LONG        
這裡是戰船的船艙。這裡現在沒有什麼人。桌子上放著一杯茶，還
有些溫熱，看來這裡的人剛出去不久。旁邊還有一張圖紙，似乎是關于
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
