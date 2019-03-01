// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "翠竹園"); 
        set("long", @LONG
『有竹無肉軒』四周就是翠竹園，這裡種滿了竹，每到風清月白
的夏夜，圓月山莊的歷代主人們便會來此，一把竹椅，一壺清茶，聽
那海浪般的竹濤聲，可惜柳若鬆很久已經沒這個興致了，倒是會時常
和他的兄弟們砍竹賣錢換酒，年復一年，翠竹園中的竹子也越來越少。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "north":__DIR__"wuzhuxuan",
        ]) );
        
        set("item_desc", ([
                "bamboo": "青青的竹子隨風搖擺，你似乎可以折（pick）幾根下來。\n",
                "竹子": "青青的竹子隨風搖擺，你似乎可以折（pick）幾根下來。\n",
        ]) );
        set("coor/x",-610);
        set("coor/y",210);
        set("coor/z",80);
        setup();
} 
void init()
{
        add_action("do_pick", "pick");
} 
int do_pick(string arg)
{
        object bamboo;
        if ( !arg && arg != "bamboo" && arg != "竹子" )
                return notify_fail("你要折什麼？\n");
        if((int) query("picked") <= 3)
        {
                write("你折了一根青青的竹子，小心的放在懷裡。\n");
                bamboo = new("/clone/weapon/bamboo");
                bamboo->move(this_player());
                addn("picked",1);
           return 1;
        }
        else
        write("竹子已經被人折光了！！\n");
        return 1;
} 
void reset()
{
        :: reset();
        delete("picked");
}    
