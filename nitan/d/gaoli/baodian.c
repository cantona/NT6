// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "大雄寶殿");
        set("long", @LONG        
這裡是靈靜寺的大雄寶殿。有幾個僧人正在這裡誦經念佛。這裡香
氣繚繞，一派莊嚴的氣氛。有幾個人正在這裡跪拜佛祖，口中念念有詞，
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
