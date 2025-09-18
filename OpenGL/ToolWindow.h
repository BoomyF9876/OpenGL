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
		static float Intensity = 1.0f; // Default to 100%

	private: System::Windows::Forms::CheckBox^ checkBoxRedChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxGreenChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxBlueChannel;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TrackBar^ trackBar1;
		   
	public:
	ToolWindow(void)
	{
		InitializeComponent();
		RenderRedChannel = checkBoxRedChannel->Checked;
		RenderGreenChannel = checkBoxGreenChannel->Checked;
		RenderBlueChannel = checkBoxBlueChannel->Checked;
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

#pragma region Windows Form Designer generated code
	private: System::Void checkBoxRedChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderRedChannel = checkBoxRedChannel->Checked;
	}
	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderGreenChannel = checkBoxGreenChannel->Checked;
	}
	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderBlueChannel = checkBoxBlueChannel->Checked;
	}
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		Intensity = trackBar1->Value / 100.0f;
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}


	void InitializeComponent(void)
		{
		this->checkBoxRedChannel = (gcnew System::Windows::Forms::CheckBox());
		this->checkBoxGreenChannel = (gcnew System::Windows::Forms::CheckBox());
		this->checkBoxBlueChannel = (gcnew System::Windows::Forms::CheckBox());
		this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
		this->label1 = (gcnew System::Windows::Forms::Label());
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
		this->SuspendLayout();
		// 
		// checkBoxRedChannel
		// 
		this->checkBoxRedChannel->AutoSize = true;
		this->checkBoxRedChannel->Location = System::Drawing::Point(84, 95);
		this->checkBoxRedChannel->Margin = System::Windows::Forms::Padding(6);
		this->checkBoxRedChannel->Name = L"checkBoxRedChannel";
		this->checkBoxRedChannel->Size = System::Drawing::Size(211, 36);
		this->checkBoxRedChannel->TabIndex = 0;
		this->checkBoxRedChannel->Text = L"RedChannel";
		this->checkBoxRedChannel->UseVisualStyleBackColor = true;
		this->checkBoxRedChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxRedChannel_CheckedChanged);
		// 
		// checkBoxGreenChannel
		// 
		this->checkBoxGreenChannel->AutoSize = true;
		this->checkBoxGreenChannel->Location = System::Drawing::Point(84, 227);
		this->checkBoxGreenChannel->Margin = System::Windows::Forms::Padding(6);
		this->checkBoxGreenChannel->Name = L"checkBoxGreenChannel";
		this->checkBoxGreenChannel->Size = System::Drawing::Size(238, 36);
		this->checkBoxGreenChannel->TabIndex = 1;
		this->checkBoxGreenChannel->Text = L"GreenChannel";
		this->checkBoxGreenChannel->UseVisualStyleBackColor = true;
		this->checkBoxGreenChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxGreenChannel_CheckedChanged);
		// 
		// checkBoxBlueChannel
		// 
		this->checkBoxBlueChannel->AutoSize = true;
		this->checkBoxBlueChannel->Location = System::Drawing::Point(84, 356);
		this->checkBoxBlueChannel->Margin = System::Windows::Forms::Padding(6);
		this->checkBoxBlueChannel->Name = L"checkBoxBlueChannel";
		this->checkBoxBlueChannel->Size = System::Drawing::Size(217, 36);
		this->checkBoxBlueChannel->TabIndex = 2;
		this->checkBoxBlueChannel->Text = L"BlueChannel";
		this->checkBoxBlueChannel->UseVisualStyleBackColor = true;
		this->checkBoxBlueChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxBlueChannel_CheckedChanged);
		// 
		// trackBar1
		// 
		this->trackBar1->Location = System::Drawing::Point(84, 520);
		this->trackBar1->Maximum = 100;
		this->trackBar1->Name = L"trackBar1";
		this->trackBar1->Size = System::Drawing::Size(842, 114);
		this->trackBar1->TabIndex = 3;
		this->trackBar1->TickFrequency = 10;
		this->trackBar1->Value = 100;
		this->trackBar1->Scroll += gcnew System::EventHandler(this, &ToolWindow::trackBar1_Scroll);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(84, 454);
		this->label1->Name = L"Intensity";
		this->label1->Size = System::Drawing::Size(92, 32);
		this->label1->TabIndex = 4;
		this->label1->Text = L"Intensity";
		this->label1->Click += gcnew System::EventHandler(this, &ToolWindow::label1_Click);
		// 
		// ToolWindow
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(16, 31);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1132, 905);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->trackBar1);
		this->Controls->Add(this->checkBoxBlueChannel);
		this->Controls->Add(this->checkBoxGreenChannel);
		this->Controls->Add(this->checkBoxRedChannel);
		this->Margin = System::Windows::Forms::Padding(6);
		this->Name = L"ToolWindow";
		this->Text = L"ToolWindow";
		this->ResumeLayout(false);
		this->PerformLayout();

	}


};
}
