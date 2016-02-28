import webbrowser  



if __name__=="__main__":
    urls = []
    
    if len(urls) == 0 :
        
        file_object = open("urls.txt")
        
        try:
         
            all_the_text = file_object.read( )
        
        finally:
         
            file_object.close( )
            
	urls = all_the_text.split()
    #urls =  all_the_text
	
    for url in urls :
    	print url
    	webbrowser.open_new_tab(url)