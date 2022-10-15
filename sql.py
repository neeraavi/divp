import sqlite3
from sqlite3 import Error
import math

def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Error as e:
        print(e)
    return conn


def select_transactions_by_yymm(conn, yy, mm):
    cur = conn.cursor()
    cur.execute("""SELECT * 
        FROM transactions 
        WHERE yy=? and mm=? 
        union ALL 
        select '~ Total', ' ',  ' ', ' ', ' ', ' ',round(sum(cost)) 
        from transactions 
        WHERE yy =? and mm=? 
        order by name
        """, (yy, mm, yy, mm,))
    rows = cur.fetchall()
    for row in rows:
        print(row)


def create_table(conn, create_table_sql):
    try:
        c = conn.cursor()
        c.execute(create_table_sql)
    except Error as e:
        print(e)

def create_transactions_table(conn):
    sql_create_transactions_table = """ CREATE TABLE IF NOT EXISTS "transactions" (
                "name"  TEXT,
                "operation" TEXT,
                "yy"    INTEGER,
                "mm"    INTEGER,
                "dd"    INTEGER,
                "nos"   INTEGER,
                "cost"  REAL
                ); """
    create_table(conn, sql_create_transactions_table)

def insert_transaction(conn, item):
    sql = ''' INSERT INTO transactions(name,operation,yy,mm,dd,nos,cost)
              VALUES(?,?,?,?,?,?,?) '''
    cur = conn.cursor()
    cur.execute(sql, item)
    conn.commit()
    return cur.lastrowid


def process_file(conn, filename, line_processor, meta_processor):
    res=[]
    with open(filename) as file:
        for line in file:
            r=line_processor(conn, line.rstrip())
            if r is not None:
                res.append(r)
    meta_processor(conn, res)


def dummy_processor(conn, res_list):
    pass

def transactions_processor(conn, line):
    if not line.startswith('#'):
        (name, yy, mm, dd, operation, nos, cost) = line.replace(' ', '').split('-')
        # print(line)
        print(name, yy, mm, dd)
        item = (name, operation, yy, mm, dd, nos, cost)
        insert_transaction(conn, item)
    return None


def fill_transactions(conn):
    f = 'd:/tmp/sql/akt.txt'
    process_file(conn, f, transactions_processor, dummy_processor)


def drop_table(conn, tab):
    sql_drop_table = 'DROP TABLE IF EXISTS "'+tab+'";'
    c = conn.cursor()
    c.execute(sql_drop_table)
    conn.commit()

def create_calendar(conn, cal_name):    
    #_yearly_update_
    sql_create_table = 'CREATE TABLE IF NOT EXISTS "' + cal_name + """" (
       "Month" TEXT,
       "2022"  INTEGER,
       "2021"  INTEGER,
       "2020"  INTEGER,
       "2019"  INTEGER,
       "2018"  INTEGER,
       "2017"  INTEGER,
       "2016"  INTEGER,
       "2015"  INTEGER
       ); """

    drop_table(conn, cal_name)
    c = conn.cursor()
    c.execute(sql_create_table)
    conn.commit()

def create_investment_calendar(conn):
    create_calendar(conn, 'investment_calendar')    

def sum_transactions_by_yymm(conn, yy, mm, op):
    cur     = conn.cursor()
    cur.execute("select sum(cost) from transactions WHERE yy=? and mm=? and operation=?", (yy, mm, op))
    rows = cur.fetchall()
    #for row in rows:
    #    print(row)
    return rows[0][0] or 0

def insert_inv_cal_entry(conn, item):
    sql = ''' INSERT INTO investment_calendar
              VALUES(?,?,?, ?,?,?, ?,?,?) '''  #_yearly_update_
    cur = conn.cursor()
    cur.execute(sql, item)
    conn.commit()
    return cur.lastrowid

def fill_investment_calendar(conn):
    start_year = 2015
    current_year = 2022  #_yearly_update_
    for mm in range(1, 13):
        val=[mm] #TODO: replace with month abbr
        for yy in range(current_year, start_year - 1, -1):
            b = sum_transactions_by_yymm(conn, yy, mm, 'Buy') or 0
            s = sum_transactions_by_yymm(conn, yy, mm, 'Sell') or 0
            v = math.ceil(b - s)
            #print(yy, mm, v )
            val.append(v)
        print(val)
        insert_inv_cal_entry(conn, val)

def sum_investments_by_yy(conn, yy):
    start_year = 2015
    current_year = 2022  #_yearly_update_

    cur = conn.cursor()
    val=['Total']
    for yy in range(current_year, start_year - 1, -1):
        q = 'select sum("' + str(yy) +'") from investment_calendar'
        cur.execute(q)
        rows = cur.fetchall()
        v = rows[0][0] or 0
        val.append(v)
    print(val)
    insert_inv_cal_entry(conn, val)        

def sum_overall_invested(conn):
    cur = conn.cursor()
     #_yearly_update_
    q = ''' select "2022"+ "2021"+ "2020"+ "2019"+ "2018"+ "2017"+ "2016"+ "2015" 
            from investment_calendar 
            where Month="Total" '''
    cur.execute(q)
    rows = cur.fetchall()
    v = rows[0][0] or 0
    val=['Σ', v, ' ', ' ',' ', ' ',' ', ' ',' '] #_yearly_update_
    insert_inv_cal_entry(conn, val)
    val=['ϕ', math.ceil(v/8), ' ', ' ',' ', ' ',' ', ' ',' '] #_yearly_update_
    insert_inv_cal_entry(conn, val)
    #for row in rows:
    #    print(row)
    

def execute_sql(conn, query):
    cur     = conn.cursor()
    cur.execute(query)
    rows = cur.fetchall()
    for row in rows:
        print(row)

def create_dividend_table(conn):
    drop_table(conn, 'dividends')
    sql_create_table = """ CREATE TABLE IF NOT EXISTS "dividends" (
                "name"  TEXT,
                "freq" TEXT,
                "mm"    INTEGER,                
                "yy"    INTEGER,
                "nos"   INTEGER,
                "dps"   REAL,
                "before" REAL,
                "after"  REAL,
                "where" TEXT
                ); """
    create_table(conn, sql_create_table)

def insert_dividend(conn, item):
    sql = ''' INSERT INTO dividends(name, freq, mm, yy, nos, dps, before, after, "where") 
              VALUES(?,?,? ,?,?,?, ?,?,?) '''
    cur = conn.cursor()
    cur.execute(sql, item)
    conn.commit()
    return cur.lastrowid

def insert_dividends_from_list(conn, div_list):
    sql = ''' INSERT INTO dividends(name, freq, mm, yy, nos, dps, before, after, "where") 
              VALUES(?,?,? ,?,?,?, ?,?,?) '''
    cur = conn.cursor()
    #a=div_list[1:10]
    #print(a)
    cur.executemany(sql, div_list)
    conn.commit()
    return cur.lastrowid

def dividend_processor(conn, line):
    if not line.startswith('#'):
        parts = line.replace(' ', '').split('-')
        (name, freq, mm, yy, nos, dps, before, after,where)=(0,0,0, 0,0,0, 0,0,'.')
#        print(line, len(parts))
        if len(parts) > 8:
            (name, freq, mm, yy, nos, dps, before, after,where) = parts
        elif len(parts) > 7:
            (name, freq, mm, yy, nos, dps, before, after) = parts
        else:
            (name, freq, mm, yy, nos, dps, before) = parts
            after = round(float(before)*.75,2)
        if dps == '':
            dps = round(float(before)/int(nos),2)

        #print(name, freq, mm, yy, nos, dps, before, after,where)
        item =(name, freq, int(mm), int(yy), int(nos), float(dps), float(before), float(after),where)
        return item
        #insert_dividend(conn, item)

def dividend_meta_processor(conn, res_list):
    insert_dividends_from_list(conn, res_list)


def fill_dividends(conn):
    f = 'd:/tmp/sql/div.txt'
    process_file(conn, f, dividend_processor, dividend_meta_processor)

def create_dividend_calendar(conn):
    create_calendar(conn, 'dividend_calendar_before')    
    create_calendar(conn, 'dividend_calendar_after')    

def fill_dividend_calendar(conn):
    start_year = 2015
    current_year = 2022  #_yearly_update_
    for mm in range(1, 13):
        bef=[mm] #TODO: replace with month abbr
        aft=[mm] #TODO: replace with month abbr
        for yy in range(current_year, start_year - 1, -1):
            v = sum_dividends_by_yymm(conn, yy, mm) 
            b = round(v[0]) #before tax
            a = round(v[1]) #after tax
            print(yy, mm,  b, a)
            bef.append(b)
            aft.append(a)
        print(bef,aft)
        insert_div_cal_entry(conn, 'dividend_calendar_before',  bef)
        insert_div_cal_entry(conn, 'dividend_calendar_after',  aft)

def sum_dividends_by_yymm(conn, yy, mm):
    cur     = conn.cursor()
    cur.execute("select sum(before), sum(after) from dividends WHERE yy=? and mm=? ", (yy, mm))
    row = cur.fetchall()
    #for row in rows:
    #    print(row)
    return [row[0][0] or 0, row[0][1] or 0]

def insert_div_cal_entry(conn, cal_name, item):
    sql = ''' INSERT INTO "'''+cal_name+'''"
              VALUES(?,?,?, ?,?,?, ?,?,?) '''  #_yearly_update_
    cur = conn.cursor()
    cur.execute(sql, item)
    conn.commit()
    return cur.lastrowid

def main():
    database = r"d:/tmp/sql/testdb.db"
    conn = create_connection(database)
    with conn:
        #create_transactions_table(conn)
        #fill_transactions(conn)
        select_transactions_by_yymm(conn, 2021, 3)
        
        #create_investment_calendar(conn)
        #fill_investment_calendar(conn)
        #sum_investments_by_yy(conn,2022)
        #sum_overall_invested(conn)

        #create_dividend_table(conn)
        #fill_dividends(conn)

        create_dividend_calendar(conn)
        fill_dividend_calendar(conn)

if __name__ == '__main__':
    main()


