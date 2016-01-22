#coding=utf-8
from PIL import Image



if __name__ == "__main__" :
	# 打开一个jpg图像文件，注意路径要改成你自己的:
	im = Image.open('./test.jpg')
	# 获得图像尺寸:
	width, height = im.size
	print "the image size Width = %d, Height = %d" % (width, height)
	
	# 缩放到50%:
	im.thumbnail((width//2, height//2))
	print "resize Width = %d, Height = %d" % (im.size)
	# 把缩放后的图像用jpeg格式保存:
	im.save('./thumbnail.jpg', 'jpeg')