import tkinter as tk
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt
import os

class MainWindow:
    def __init__(self):

        self.root=tk.Tk()
        start_image=tk.PhotoImage(file="background.png")
        self.root.geometry(str(start_image.width())+"x"+str(start_image.height()))

        self.centerX=start_image.width()/2
        self.centerY=start_image.height()/2

        self.root.title("Générateur Aléatoire")
        self.root.resizable(False,False)

        
        self.canvas=tk.Canvas(self.root,width=start_image.width(),height=start_image.height())
        self.canvas.pack()
        self.canvas.create_image(self.centerX,self.centerY,image=start_image)

        
        self.start_button=tk.Button(self.canvas,text="Start Simulation",bg="green",fg="white",command=lambda:self.generate(),font=("Lucida Console",25))
        self.start_button.place(relx=0.5,rely=0.5,anchor=tk.CENTER)

        self.root.mainloop()

    def generate(self):
        self.start_button.destroy()
        text_info=tk.Label(self.canvas,bg="grey",fg="white",text="launch c program...",font=("New Roman",20))
        text_info.place(relx=0.5,rely=0.5,anchor=tk.CENTER)
        self.canvas.update()
        os.system("make PROGRAM --no-print-directory")
        text_info.configure(text="processing...")
        print("processing...")

        self.tb1=np.loadtxt("grayscale.txt",dtype=np.uint8)
        im= Image.fromarray(self.tb1,mode="P")
        im=im.resize((600,600))
        im.save("img1.png")
        del im

        self.tb2=np.loadtxt("rgb256.txt",dtype=np.uint8)
        tb3=self.tb2.reshape((300,300,3))
        
        im=Image.fromarray(tb3,mode="RGB")
        im=im.resize((600,600))
        im.save("img2.png")
        del im,tb3

        text_info.destroy()
        print("calling main menu...")
        self.root.after(100,self.menu)

    def menu(self):
        button1=tk.Button(self.canvas,text="Black and White Image",command=lambda:self.display_image("img1.png"))
        button1.place(x=self.centerX,y=self.centerY-100,anchor=tk.CENTER)

        button2=tk.Button(self.canvas,text="RGB256 Image",command=lambda:self.display_image("img2.png"))
        button2.place(x=self.centerX,y=self.centerY-50,anchor=tk.CENTER)

        button3=tk.Button(self.canvas,text="First 100 values generated",command=self.plot1)
        button3.place(x=self.centerX,y=self.centerY+0,anchor=tk.CENTER)

        button4=tk.Button(self.canvas,text="Occurence Graphics",command=self.plot2)
        button4.place(x=self.centerX,y=self.centerY+50,anchor=tk.CENTER)

        button5=tk.Button(self.canvas,text="Mean evolution",command=self.plot3)
        button5.place(x=self.centerX,y=self.centerY+100,anchor=tk.CENTER)


    def display_image(self,path_image):
        window=tk.Toplevel()
        img=tk.PhotoImage(file=path_image)
        window.geometry(str(img.width())+"x"+str(img.height()+20))
        centerX=img.width()/2
        centerY=img.height()/2

        window.title(path_image)
        window.resizable(False,False)
        
        canvas=tk.Canvas(window,width=img.width(),height=img.height())
        canvas.pack()
        tk.Label(window,text="press escape to quit...",width=img.width(),height=20,bg="grey",fg="white").pack()
        canvas.create_image(centerX,centerY,image=img)

        window.bind("<Escape>",lambda e:window.destroy())
        window.mainloop()

    def plot1(self):
        plt.title("Random Generation")
        plt.plot(self.tb1[0][:100],label="seed=11")
        plt.plot(self.tb2[0][:100],label="seed=12")
        plt.legend(loc='lower left', shadow=True)
        plt.show()  

    def plot2(self):
        l=np.bincount(self.tb2.flatten())
        plt.title("Occurence of each value")
        plt.bar(np.arange(256),l)
        plt.show()

    def plot3(self):
        plt.title("Mean evolution as function of the number of draws")
        for l in [self.tb1.flatten(),self.tb2.flatten()]:
            l1=list()
            s=0
            c=0
            for i in l:
                c+=1
                s+=i
                l1.append(s/c)
        
            plt.plot(l1)
            del l1
        plt.show()

MainWindow()