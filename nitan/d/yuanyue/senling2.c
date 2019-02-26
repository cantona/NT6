// This program is a part of NITAN MudLIB

inherit ROOM;
void create()
{
        set("short", "松林"); 
        set("long", @LONG
這裏是圓月山莊後園一片密密的松木林，四周一片寂靜。松針落
的遍地都是，幾乎把整個小路鋪成了條軟軟的鬆毯，不知名的野兔偷
偷逃過，小路旁就是條靜靜流淌的小溪，溪水上漂浮着松針黃葉，蕩
開枝葉，依稀可看到溪水碧綠如鏡，清澈見底。撥開路旁一塊石碑的
泥垢，隱約可以看到其上寫着『瀝泉』二字。
LONG );
        set("outdoors", "wansong");
        set("type","forest");
        set("exits",([
                "north":__DIR__"senling3",
                "southeast":__DIR__"senling1",
        ]) );
        set("item_desc", ([
                "brook": "溪水碧綠如鏡，清澈見底，偶爾有幾根松針漂浮在水面上。\n",
                "liquan": "溪水碧綠如鏡，清澈見底，偶爾有幾根松針漂浮在水面上。\n",
                "小溪": "溪水碧綠如鏡，清澈見底，偶爾有幾根松針漂浮在水面上。\n",
                "石碑": "石碑已經年代久遠，破敗不堪，但隱約可以看到上面刻着[瀝泉]二字。\n",
                "stone": "石碑已經年代久遠，破敗不堪，但隱約可以看到上面刻着[瀝泉]二字。\n",
                "shibei": "石碑已經年代久遠，破敗不堪，但隱約可以看到上面刻着[瀝泉]二字。\n",
        ]) );
//      set("resource/water",1);
        set("liquid/name","泉水");
        set("liquid/type", "water");
        set("liquid/drunk_apply",0);
        set("coor/x",-620);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        
}  
void init()
{
        add_action("do_fillwater", "fill");
} 
int do_fillwater(string arg)
{
        object *list, ob;
        int i, can_fillwater;
        string dir;
        function f; 
        if( !arg || arg=="" ) return 0; 
        if( arg=="skin" || arg=="wineskin" ) 
        {
                list = all_inventory(this_player());
                i = sizeof(list);
                can_fillwater = 0;
                for (i=0;i<sizeof(list);i++) 
                {
                  if( (query("liquid/type", list[i]) == "alcohol") || (query("liquid/type", list[i]) == "water") )
                  {
                        ob = list[i];
                        can_fillwater = 1;
                        ob->set("liquid",([
                                "type": "water",
                                "name": "瀝泉水",
                                "remaining":query("max_liquid", ob),
                                "drunk_apply": 0,
                        ]) );
                        f = (: call_other, __FILE__, "drink_drug" :);
                        set("liquid/drink_func", bind(f,ob), ob);
                        write("你從小溪裏裝滿了瀝泉水！ \n");
                        return 1;
                   }
                }
                if (can_fillwater ==0) 
                {
                        write("你沒有裝水的東西啊....\n");
                        return 1;
                }
        }
        else 
        {
                write("你要往什麼東西里灌水？\n");
        }
        return 1;
} 
int drink_drug(object ob)
{
        set_temp("fugui_liquan", 1, this_player());
        return 0;
} 
