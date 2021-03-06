// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "芳草坪"); 
        set("long", @LONG
這裏是一塊芳草坪，綠草茵茵，蝴蝶漫舞，花香撲鼻，讓人感到
十分愜意。不禁令人就想一頭躺倒上去，好好的去睡一覺，但這裏偶
爾也會碰到菜花蛇。東面是片小樹林，向北是間卧室。
LONG );
        set("type","grassland");
        set("outdoors", "wansong");
        set("exits",([
                "west":__DIR__"grass2",
                "north":__DIR__"woshi1",
                "southwest":__DIR__"shibanlu4",
        ]) );
        set("objects",([
                "/clone/beast/caihuashe" : 1,
                __DIR__"obj/grass" : 1,
        ]) ); 
        set("coor/x",-580);
        set("coor/y",240);
        set("coor/z",80);
        setup();
} 
void init()
{
        add_action("do_search", "search");
} 
int do_search(string arg)
{
        object me,obj;
        object grass;
        me = this_player();
        grass = present("grass", this_object()); 
        if(!arg) 
        {
                write("你要在哪裏找東西？給點提示好不好，老大！\n");
                return 1;
   }
        
        if( me->is_busy() )
                return notify_fail("你上一個動作還沒有完成，不能查找。\n");
        
        if( arg == "grass" || arg == "綠草"  )
        {
                if ( !query("gotit") && ! random(5) )
                {
                        message_vision("$N蹲下身子，仔細的找了起來，發現有點東西藏在綠草下邊。\n",me);
                        obj = new("/clone/beast/caihuashe");
                        obj->move(grass);
                        set("gotit",1);
                }
                else
                {
                        message_vision("$N用手撥開草叢，仔細的查找一番，但什麼都沒有找到。\n",me);
                        me->start_busy(2);
                }
        }
        else
        {
                write("你找不到"+arg+"。\n");
                return 1;
        }
        return 1;
} 
void reset()
{
        ::reset();
        if( query("gotit") ) set("gotit",0);
}      
