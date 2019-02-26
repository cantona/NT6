//room: house1.c
//Updated by haiyan

inherit ROOM;

void create()
{
     set("short","內室");
        set("long", @LONG
這是一個精雅的小舍，一進門便可聞到一陣濃冽的花香。房中掛
着一幅五女向鳳圖，圖中繪着五個宮裝美女，美目盼兮，豔麗脱俗。
屋裏還有一張茶几(teapoy)，幾張椅子，椅子上鋪着繡花錦墊，西面
有一扇洞形門通向後廳。
LONG );

     set("exits",([
         "west" : __DIR__"huoting",
     ]));

     set("valid_startroom", 1);
     set("item_desc", ([
         "teapoy": "這張茶几似乎曾經給人移動過。\n",
     ]));

     setup();
}

void init()
{
     add_action("do_move", "move");
     add_action("do_move", "push");
}

void close_path()
{
     if (! query("exits/enter"))   return;
     message("vision","茶几又自動移了回來，蓋住了入口。\n", this_object());
     delete("exits/enter");
}

int do_move(string arg)
{
     if (! arg || arg != "teapoy" )
        return notify_fail("什麼？\n");
     else
     {
        write("你把茶几推開，露出了一個通道。\n");
        if (! query("exits/enter"))
        {
            set("exits/enter", __DIR__ "midao01");
            call_out("close_path", 5);
        }
        return 1;
     }
}