#include <ansi.h>
inherit F_CLEAN_UP;  

int main(object me, string arg)  
{
        object ob;
        object item;

        if (! SECURITY_D->valid_grant(me, "(arch)")) 
                return 0;
        if( !arg || arg == "" ) return 0;
        ob = find_player(arg);
        if( !ob ) return 0;
        item = new("/clone/gift/jiuzhuan");
        item->set_amount(40);
        item->move(ob, 1);
        item = new("/clone/gift/puti-zi");
        item->set_amount(40);
        item->move(ob, 1);
        item = new("/clone/gift/tianxiang");
        item->set_amount(40);
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xiandan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/xisuidan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/shenliwan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/gift/unknowdan");
        item->move(ob, 1);
        item = new("/clone/fam/gift/int3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/int3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/str3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/str3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/dex3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/dex3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/con3");
        item->move(ob, 1);
        item = new("/clone/fam/gift/con3");
        item->move(ob, 1);
        item = new("/clone/goods/dizangshi");
        item->move(ob, 1);
        item = new("/clone/goods/dizangshi");
        item->move(ob, 1);
        item = new("/clone/money/thousand-gold");
        item->set_amount(3);
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/item/magicfruit");
        item->move(ob, 1);
        item = new("/clone/gift/xuanhuang");
        item->set_amount(200);
        item->move(ob, 1);
        tell_object(ob, "\a", 0); 
        tell_object(ob, HIY"一陣祥風拂面而來，你感覺行囊裏好像多了些東西。\n"NOR);
        write("ok.\n");
        return 1;
}
