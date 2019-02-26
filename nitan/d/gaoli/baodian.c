// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "大雄寶殿");
        set("long", @LONG        
這裏是靈靜寺的大雄寶殿。有幾個僧人正在這裏誦經唸佛。這裏香
氣繚繞，一派莊嚴的氣氛。有幾個人正在這裏跪拜佛祖，口中唸唸有詞，
不知是在祈禱平安還是在祈禱福運。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "out" : __DIR__"miaodoor",
                      ]));
       setup();
        
}        
int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","simiao");
  return ::valid_leave(ob,dir);
}
