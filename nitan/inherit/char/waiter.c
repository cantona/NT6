// 店舖伙計程序

inherit NPC;

int is_waiter()
{
        return 1;
}

// 修改屬性
int do_modify(string arg)
{
        write(SHOP_D->do_modify(this_object(), this_player(), arg));
        return 1;
}

// 標價貨物
int do_stock(string arg)
{
        //write(SHOP_D->do_stock(this_object(), this_player(), arg));
        write(environment(this_object())->do_stock(this_object(), this_player(), arg));

        return 1;
}

// 取下貨物
int do_unstock(string arg)
{
       //write(SHOP_D->do_unstock(this_object(), this_player(), arg));
       write(environment(this_object())->do_unstock(this_object(), this_player(), arg));
       return 1;
}

// 查詢貨物列表
int do_list(string arg)
{
        //write(SHOP_D->do_list(this_object(), this_player(), arg));
        write(environment(this_object())->do_list(this_object(), this_player(), arg));
        return 1;
}

// 購買貨物
int do_buy(string arg)
{
        //return SHOP_D->do_buy(this_object(), this_player(), arg);
        write(environment(this_object())->do_buy(this_object(), this_player(), arg));
}

// 店主結帳
int do_jiezhang()
{
        write(SHOP_D->do_jiezhang(this_object(), this_player()));
        return 1;
}

// 設置、查詢貴賓
int do_invite(string arg)
{
        string msg;

        if (arg)
                msg = SHOP_D->do_invite(this_object(), this_player(), arg);
        else
                msg = SHOP_D->list_invite(this_object(), this_player());

        write(msg);
        return 1;
}

// 設置、查詢貴賓
int do_ban(string arg)
{
        string msg;
        if (arg)
                msg = SHOP_D->do_ban(this_object(), this_player(), arg);
        else
                msg = SHOP_D->list_ban(this_object(), this_player());
        write(msg);
        return 1;
}

//預約商品
int do_order(string arg)
{
        string msg;
        if (arg)
                msg = SHOP_D->do_order(this_object(), this_player(), arg);
        else
                msg = SHOP_D->list_order(this_object(), this_player());
        write(msg);
        return 1;
}

void init()
{
        if (query("id", this_player()) == query("owner", environment()))
        {
                add_action("do_stock", "stock");
                add_action("do_unstock", "unstock");
                add_action("do_jiezhang", ({ "reckoning", "jiezhang"}));
                add_action("do_modify", "modify");
                add_action("do_invite", ({ "invite", "vip" }));
                add_action("do_ban", ({ "ban", "unwelcome", }));
        }
        add_action("do_order","order");
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void die()
{
        return;
}

void unconcious()
{
        die();
}

int restore()
{
        string file;

        if (stringp(file = this_object()->query_save_file()) &&
            file_size(file + __SAVE_EXTENSION__) > 0)
                return restore_object(file);

        return 0;
}
