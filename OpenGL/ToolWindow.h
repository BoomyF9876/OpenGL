#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static bool RenderRedChannel;
		static bool RenderGreenChannel;
		static bool RenderBlueChannel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TrackBar^ LightColorR;
	public:

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ LightColorG;
	private: System::Windows::Forms::TrackBar^ LightColorB;


	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TrackBar^ RotationRate;
	private: System::Windows::Forms::TrackBar^ RotationX;
	private: System::Windows::Forms::TrackBar^ RotationY;
	private: System::Windows::Forms::TrackBar^ RotationZ;




	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;




	public:
		static float LightR = 1.0f;
		static float LightG = 1.0f;
		static float LightB = 0.5f;
		static float Rotation_Rate = 0.01f;
		static float Position_X = 200.0f;
		static float Position_Y = 0.0f;
		static float Position_Z = 0.0f;


		   
	public:
	ToolWindow(void)
	{
		InitializeComponent();

		this->LightColorR->Scroll += gcnew System::EventHandler(this, &ToolWindow::LightColorR_Scroll);
		this->LightColorG->Scroll += gcnew System::EventHandler(this, &ToolWindow::LightColorG_Scroll);
		this->LightColorB->Scroll += gcnew System::EventHandler(this, &ToolWindow::LightColorB_Scroll);
		this->RotationRate->Scroll += gcnew System::EventHandler(this, &ToolWindow::RotationRate_Scroll);
		this->RotationX->Scroll += gcnew System::EventHandler(this, &ToolWindow::RotationX_Scroll);
		this->RotationY->Scroll += gcnew System::EventHandler(this, &ToolWindow::RotationY_Scroll);
		this->RotationZ->Scroll += gcnew System::EventHandler(this, &ToolWindow::RotationZ_Scroll);
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;


	void InitializeComponent(void)
		{
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->LightColorR = (gcnew System::Windows::Forms::TrackBar());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->LightColorG = (gcnew System::Windows::Forms::TrackBar());
		this->LightColorB = (gcnew System::Windows::Forms::TrackBar());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->RotationRate = (gcnew System::Windows::Forms::TrackBar());
		this->RotationX = (gcnew System::Windows::Forms::TrackBar());
		this->RotationY = (gcnew System::Windows::Forms::TrackBar());
		this->RotationZ = (gcnew System::Windows::Forms::TrackBar());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->label9 = (gcnew System::Windows::Forms::Label());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorR))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorG))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorB))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationRate))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationX))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationY))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationZ))->BeginInit();
		this->SuspendLayout();
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(44, 41);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(152, 32);
		this->label1->TabIndex = 4;
		this->label1->Text = L"Light Color";
		// 
		// LightColorR
		// 
		this->LightColorR->Location = System::Drawing::Point(216, 105);
		this->LightColorR->Maximum = 100;
		this->LightColorR->Name = L"LightColorR";
		this->LightColorR->Size = System::Drawing::Size(812, 114);
		this->LightColorR->TabIndex = 3;
		this->LightColorR->TickFrequency = 10;
		this->LightColorR->Value = LightR;
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(117, 105);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(34, 32);
		this->label2->TabIndex = 5;
		this->label2->Text = L"R";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(117, 187);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(36, 32);
		this->label3->TabIndex = 6;
		this->label3->Text = L"G";
		// 
		// LightColorG
		// 
		this->LightColorG->Location = System::Drawing::Point(216, 187);
		this->LightColorG->Maximum = 100;
		this->LightColorG->Name = L"LightColorG";
		this->LightColorG->Size = System::Drawing::Size(812, 114);
		this->LightColorG->TabIndex = 7;
		this->LightColorG->TickFrequency = 10;
		this->LightColorG->Value = LightG * this->LightColorG->Maximum;
		// 
		// LightColorB
		// 
		this->LightColorB->Location = System::Drawing::Point(216, 269);
		this->LightColorB->Maximum = 100;
		this->LightColorB->Name = L"LightColorB";
		this->LightColorB->Size = System::Drawing::Size(812, 114);
		this->LightColorB->TabIndex = 8;
		this->LightColorB->TickFrequency = 10;
		this->LightColorB->Value = LightB * this->LightColorB->Maximum;
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Location = System::Drawing::Point(120, 269);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(33, 32);
		this->label4->TabIndex = 9;
		this->label4->Text = L"B";
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Location = System::Drawing::Point(44, 351);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(246, 32);
		this->label5->TabIndex = 10;
		this->label5->Text = L"Sun Rotation Rate";
		// 
		// RotationRate
		// 
		this->RotationRate->Location = System::Drawing::Point(155, 429);
		this->RotationRate->Maximum = 100;
		this->RotationRate->Name = L"RotationRate";
		this->RotationRate->Size = System::Drawing::Size(812, 114);
		this->RotationRate->TabIndex = 11;
		this->RotationRate->TickFrequency = 10;
		// 
		// RotationX
		// 
		this->RotationX->Location = System::Drawing::Point(188, 571);
		this->RotationX->Maximum = 300;
		this->RotationX->Minimum = 100;
		this->RotationX->Name = L"RotationX";
		this->RotationX->Size = System::Drawing::Size(812, 114);
		this->RotationX->TabIndex = 12;
		this->RotationX->TickFrequency = 10;
		this->RotationX->Value = 200;
		// 
		// RotationY
		// 
		this->RotationY->Location = System::Drawing::Point(188, 691);
		this->RotationY->Maximum = 150;
		this->RotationY->Minimum = -150;
		this->RotationY->Name = L"RotationY";
		this->RotationY->Size = System::Drawing::Size(812, 114);
		this->RotationY->TabIndex = 13;
		this->RotationY->TickFrequency = 10;
		// 
		// RotationZ
		// 
		this->RotationZ->Location = System::Drawing::Point(188, 811);
		this->RotationZ->Maximum = 300;
		this->RotationZ->Minimum = 100;
		this->RotationZ->Name = L"RotationZ";
		this->RotationZ->Size = System::Drawing::Size(812, 114);
		this->RotationZ->TabIndex = 14;
		this->RotationZ->TickFrequency = 10;
		this->RotationZ->Value = 200;
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Location = System::Drawing::Point(81, 571);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(33, 32);
		this->label6->TabIndex = 15;
		this->label6->Text = L"X";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Location = System::Drawing::Point(81, 691);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(33, 32);
		this->label7->TabIndex = 16;
		this->label7->Text = L"Y";
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Location = System::Drawing::Point(83, 811);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(31, 32);
		this->label8->TabIndex = 17;
		this->label8->Text = L"Z";
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Location = System::Drawing::Point(44, 511);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(196, 32);
		this->label9->TabIndex = 18;
		this->label9->Text = L"Earth Rotation";
		// 
		// ToolWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1132, 905);
		this->Controls->Add(this->label9);
		this->Controls->Add(this->label8);
		this->Controls->Add(this->label7);
		this->Controls->Add(this->label6);
		this->Controls->Add(this->RotationZ);
		this->Controls->Add(this->RotationY);
		this->Controls->Add(this->RotationX);
		this->Controls->Add(this->RotationRate);
		this->Controls->Add(this->label5);
		this->Controls->Add(this->label4);
		this->Controls->Add(this->LightColorB);
		this->Controls->Add(this->LightColorG);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->LightColorR);
		this->Margin = System::Windows::Forms::Padding(6);
		this->Name = L"ToolWindow";
		this->Text = L"ToolWindow";
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorR))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorG))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LightColorB))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationRate))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationX))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationY))->EndInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->RotationZ))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}



	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: 
		System::Void LightColorR_Scroll(System::Object^ sender, System::EventArgs^ e) {
			LightR = this->LightColorR->Value / 100.0f;
		}

	   System::Void LightColorG_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   LightG = this->LightColorG->Value / 100.0f;
	   }

	   System::Void LightColorB_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   LightB = this->LightColorB->Value / 100.0f;
	   }

	   System::Void RotationRate_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   Rotation_Rate = this->RotationRate->Value / 10000.0f;
	   }

	   System::Void RotationX_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   Position_X = this->RotationX->Value;
	   }

	   System::Void RotationY_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   Position_Y = this->RotationY->Value;
	   }

	   System::Void RotationZ_Scroll(System::Object^ sender, System::EventArgs^ e) {
		   Position_Z = this->RotationZ->Value;
	   }
};
}
