// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "天台");
        set("long", @LONG
這裏高麗的天台。這裏是求神祭天的地方。下面是一個大廣場，寬
闊無比。從這裏可以看到南邊高麗城的風光。這裏有幾個香燭和其他求
神的東西，看起來有些神祕。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southdown" : __DIR__"guangchang",
                //"northup":__DIR__"tiantai",
        ]));
       setup();
        
}

int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","tiantai");
  return ::valid_leave(ob,dir);
}
