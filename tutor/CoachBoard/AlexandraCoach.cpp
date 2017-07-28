#include "CoachBoard/AlexandraCoach.h"
#include "Log.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AlexandraCoach::AlexandraCoach(repository::IProfile &profile)
    : m_profile(profile)
{
    LOG(Note, "Enter AlexandraCoach::AlexandraCoach()");
}

void AlexandraCoach::PrepareLesson()
{
    LOG(Note, "Enter AlexandraCoach::PrepareLesson()");

    auto words = m_profile.GetLanguage().GetDictionary().GetNWordPairs(5);

    MultipleQuestionsStep *step =
            new MultipleQuestionsStep(*this, "Translate the word", words);
    x_AddStepPage(std::unique_ptr<StepPage>(step));

    m_results.assign(5, 0);

    {
        QFile file(":/html/templates/tests/Summary");
        file.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&file);
        QString html =  in.readAll();
        m_summaryStep = new SummaryStep(*this, "Test Results", html);
        m_summaryStep->signalChanged(0, 0, m_results.size());
        x_AddStepPage(std::unique_ptr<StepPage>(m_summaryStep));
    }
}

void AlexandraCoach::setAnswerStatus(size_t questionIndex, int status)
{
    m_results[questionIndex] = status;
    int correct = std::count(m_results.begin(), m_results.end(), 1);
    int mistakes = std::count(m_results.begin(), m_results.end(), -1);
    m_summaryStep->signalChanged(correct, mistakes, m_results.size());
}

void AlexandraCoach::MultipleQuestionsStep::onanswer(QString value)
{
    m_answers.push_back(value);
    if (value == m_questions[m_questionIndex].second)
        ++m_correct;
    else
        ++m_mistakes;
    x_MoveNext();
}

void AlexandraCoach::MultipleQuestionsStep::onskip()
{
    m_answers.push_back("");
    ++m_skipped;
    x_MoveNext();
}

void AlexandraCoach::MultipleQuestionsStep::x_MoveNext()
{
    ++m_questionIndex;
    emit invalidated();
    if (m_questionIndex < m_questions.size())
        Update("Translate the word", m_questions[m_questionIndex].first);
    else {
        Update("Translate the word", "Resume");
        emit finished();
    }
}
