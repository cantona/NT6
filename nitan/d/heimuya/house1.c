//room: house1.c
//Updated by haiyan

inherit ROOM;

void create()
{
     set("short","內室");
        set("long", @LONG
這是一個精雅的小舍，一進門便可聞到一陣濃冽的花香。房中掛
著一幅五女向鳳圖，圖中繪著五個宮裝美女，美目盼兮，艷麗脫俗。
屋裡還有一張茶幾(teapoy)，幾張椅子，椅子上舖著繡花錦墊，西面
有一扇洞形門通向後廳。
LONG );

     set("exits",([
         "west" : __DIR__"huoting",
     ]));

     set("valid_startroom", 1);
     set("item_desc", ([
         "teapoy": "這張茶幾似乎曾經給人移動過。\n",
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
     message("vision","茶幾又自動移了回來，蓋住了入口。\n", this_object());
     delete("exits/enter");
}

int do_move(string arg)
{
     if (! arg || arg != "teapoy" )
        return notify_fail("什麼？\n");
     else
     {
        write("你把茶幾推開，露出了一個通道。\n");
        if (! query("exits/enter"))
        {
            set("exits/enter", __DIR__ "midao01");
            call_out("close_path", 5);
        }
        return 1;
     }
}