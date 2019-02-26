// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "有竹無肉軒"); 
        set("long", @LONG
這裏便是『有竹無肉軒』，也和其他種滿了竹子的院子一樣，原
先本叫『聽竹軒』。可是等到王動作主人的時候，就替它改了個名字，
叫『有竹無肉軒』，因為他覺得『聽竹』這名字本來雖很雅，現在卻
已變得很俗。他認為第一個用『聽竹』作軒名的人雖然是個很風雅的
聰明人，但第八十個用『聽竹』作軒名的人就是俗不可耐的笨蛋了。
軒中三面都開了很大的窗子，向外望去，滿眼幽幽翠竹。
LONG );
        
        set("type","house");
        set("indoors", "fugui");
        set("exits",([
                "east":__DIR__"suishilu2",
                "west":__DIR__"cuizhuyuan1",
                "south":__DIR__"cuizhuyuan2",
                "north":__DIR__"cuizhuyuan3",
        ]) ); 
        set("coor/x",-610);
        set("coor/y",220);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
} 
